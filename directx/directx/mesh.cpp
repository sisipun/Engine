#include <optional>
#include <unordered_map>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "imgui/imgui.h"
#include "mesh.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "vertex.h"


Mesh::Mesh(const Renderer& renderer, std::vector<std::unique_ptr<Bindable>> bindables) noexcept
{
	if (!isStaticInitialized())
	{
		addStaticBind(std::make_unique<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	for (auto& bindable : bindables)
	{
		if (auto indexBuffer = dynamic_cast<IndexBuffer*>(bindable.get()))
		{
			addIndexBuffer(std::unique_ptr<IndexBuffer>(indexBuffer));
			bindable.release();
		}
		else
		{
			addBind(std::move(bindable));
		}
	}

	addBind(std::make_unique<TransformCbuf>(renderer, *this));
}

void Mesh::draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept
{
	DirectX::XMStoreFloat4x4(&transform, accumulatedTransform);
	Drawable::draw(renderer);
}

DirectX::XMMATRIX Mesh::getTransform() const noexcept
{
	return DirectX::XMLoadFloat4x4(&transform);
}

Node::Node(const std::string& name, std::vector<Mesh*> meshes, const DirectX::XMMATRIX& transform) noexcept : name(name), meshes(meshes)
{
	DirectX::XMStoreFloat4x4(&this->transform, transform);
	DirectX::XMStoreFloat4x4(&this->appliedTransform, DirectX::XMMatrixIdentity());
}

void Node::draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept
{
	const auto currentTrasnform = DirectX::XMLoadFloat4x4(&appliedTransform) * DirectX::XMLoadFloat4x4(&transform) * accumulatedTransform;
	for (const auto mesh : meshes)
	{
		mesh->draw(renderer, currentTrasnform);
	}
	for (const auto& child : children)
	{
		child->draw(renderer, currentTrasnform);
	}
}

void Node::addChild(std::unique_ptr<Node> child) noexcept
{
	children.push_back(std::move(child));
}

void Node::spawnControlTree(int& nodeIndex, std::optional<int>& selectedIndex, Node*& selectedNode) const noexcept
{
	const int currentNodeIndex = nodeIndex;
	nodeIndex++;
	const auto nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow
		| ((currentNodeIndex == selectedIndex.value_or(-1)) ? ImGuiTreeNodeFlags_Selected : 0)
		| ((children.size() == 0) ? ImGuiTreeNodeFlags_Leaf : 0);

	bool expanded = ImGui::TreeNodeEx((void*)(intptr_t)currentNodeIndex, nodeFlags, name.c_str());
	
	if (ImGui::IsItemClicked())
	{
		selectedIndex = currentNodeIndex;
		selectedNode = const_cast<Node*>(this);
	}

	if (expanded)
	{
		for (const auto& child : children)
		{
			child->spawnControlTree(nodeIndex, selectedIndex, selectedNode);
		}
		ImGui::TreePop();
	}
}

void Node::setAppliedTransform(DirectX::FXMMATRIX transform) noexcept
{
	DirectX::XMStoreFloat4x4(&appliedTransform, transform);
}

class ModelControlWindow
{
public:
	void spawn(const Node& root) noexcept
	{
		int nodeIndex = 0;
		if (ImGui::Begin("Model"))
		{
			ImGui::Columns(2, nullptr, true);
			root.spawnControlTree(nodeIndex, selectedIndex, selectedNode);

			ImGui::NextColumn();
			if (selectedNode != nullptr)
			{
				auto& transform = transforms[*selectedIndex];
				ImGui::Text("Orientation");
				ImGui::SliderAngle("Roll", &transform.roll, -180.0f, 180.0f);
				ImGui::SliderAngle("Pitch", &transform.pitch, -180.0f, 180.0f);
				ImGui::SliderAngle("Yaw", &transform.yaw, -180.0f, 180.0f);

				ImGui::Text("Position");
				ImGui::SliderFloat("X", &transform.x, -20.0f, 20.0f);
				ImGui::SliderFloat("Y", &transform.y, -20.0f, 20.0f);
				ImGui::SliderFloat("Z", &transform.z, -20.0f, 20.0f);
			}
		}
		ImGui::End();
	}

	DirectX::XMMATRIX getTransform() const noexcept
	{
		const auto& transform = transforms.at(*selectedIndex);
		return DirectX::XMMatrixRotationRollPitchYaw(transform.pitch, transform.yaw, transform.roll) *
			DirectX::XMMatrixTranslation(transform.x, transform.y, transform.z);
	}

	Node* getSelectedNode() const noexcept
	{
		return selectedNode;
	}

private:
	std::optional<int> selectedIndex;
	Node* selectedNode;
	struct TransformParameters
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
	std::unordered_map<int, TransformParameters> transforms;
};

Model::Model(const Renderer& renderer, const std::string fileName) noexcept : controlWindow(std::make_unique<ModelControlWindow>())
{
	Assimp::Importer importer;
	const auto model = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	for (size_t i = 0; i < model->mNumMeshes; i++)
	{
		meshes.push_back(parseMesh(renderer, *model->mMeshes[i]));
	}

	root = parseNode(*model->mRootNode);
}

Model::~Model() noexcept
{
}

void Model::draw(const Renderer& renderer) const noexcept
{
	if (auto node = controlWindow->getSelectedNode())
	{
		node->setAppliedTransform(controlWindow->getTransform());
	}
	root->draw(renderer, DirectX::XMMatrixIdentity());
}

void Model::spawnControlWindow() noexcept
{
	controlWindow->spawn(*root);
}

std::unique_ptr<Mesh> Model::parseMesh(const Renderer& renderer, const aiMesh& mesh) const noexcept
{
	VertexBufferData vertexBufferData(std::move(VertexLayout()
		.append(VertexLayout::POSITION3D)
		.append(VertexLayout::NORMAL)));

	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		vertexBufferData.emplaceBack(
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mVertices[i]),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mNormals[i])
		);
	}

	std::vector<unsigned short> indices;
	indices.reserve(mesh.mNumFaces * 3);
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	std::vector<std::unique_ptr<Bindable>> bindables;

	bindables.push_back(std::make_unique<VertexBuffer>(renderer, vertexBufferData));
	bindables.push_back(std::make_unique<IndexBuffer>(renderer, indices));

	auto vertexShader = std::make_unique<VertexShader>(renderer, L"phong_vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();

	bindables.push_back(std::move(vertexShader));
	bindables.push_back(std::make_unique<PixelShader>(renderer, L"phong_pixel.cso"));

	bindables.push_back(std::make_unique<InputLayout>(renderer, vertexBufferData.getLayout().getDescLayout(), vertexShaderBytecode));

	struct ConstantData
	{
		DirectX::XMFLOAT3 materialColor = { 0.6f, 0.6f, 0.8f };
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[3];
	} constData;
	bindables.push_back(std::make_unique<PixelConstantBuffer<ConstantData>>(renderer, constData, 2));

	return std::make_unique<Mesh>(renderer, std::move(bindables));
}

std::unique_ptr<Node> Model::parseNode(const aiNode& node) const noexcept
{
	const auto transform = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&node.mTransformation)));

	std::vector<Mesh*> currentMeshes;
	currentMeshes.reserve(node.mNumMeshes);
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		const auto meshIndex = node.mMeshes[i];
		currentMeshes.push_back(meshes.at(meshIndex).get());
	}

	auto parsedNode = std::make_unique<Node>(node.mName.C_Str(), std::move(currentMeshes), transform);
	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		parsedNode->addChild(parseNode(*node.mChildren[i]));
	}

	return parsedNode;
}