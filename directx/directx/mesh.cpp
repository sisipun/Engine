#include <optional>
#include <unordered_map>
#include <sstream>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "imgui/imgui.h"

#include "mesh.h"
#include "bindable_store.h"
#include "constant_buffer.h"
#include "index_buffer.h"
#include "input_layout.h"
#include "pixel_shader.h"
#include "topology.h"
#include "transform_cbuf.h"
#include "vertex_buffer.h"
#include "vertex_shader.h"
#include "vertex.h"
#include "texture.h"
#include "sampler.h"
#include "blender.h"
#include "rasterizer.h"
#include "dx_math.h"


Mesh::Mesh(const Renderer& renderer, std::vector<std::shared_ptr<Bindable>> bindables) noexcept
{
	addBind(BindableStore::resolve<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	for (auto& bindable : bindables)
	{
		addBind(std::move(bindable));
	}

	addBind(std::make_shared<TransformCbuf>(renderer, *this));
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

Node::Node(int id, const std::string& name, std::vector<Mesh*> meshes, const DirectX::XMMATRIX& transform) noexcept : id(id), name(name), meshes(meshes)
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

void Node::spawnControlTree(Node*& selectedNode) const noexcept
{
	const int selectedId = (selectedNode == nullptr) ? -1 : selectedNode->getId();
	const auto nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow
		| ((id == selectedId) ? ImGuiTreeNodeFlags_Selected : 0)
		| ((children.size() == 0) ? ImGuiTreeNodeFlags_Leaf : 0);

	bool expanded = ImGui::TreeNodeEx((void*)(intptr_t)id, nodeFlags, name.c_str());

	if (ImGui::IsItemClicked())
	{
		selectedNode = const_cast<Node*>(this);
	}

	if (expanded)
	{
		for (const auto& child : children)
		{
			child->spawnControlTree(selectedNode);
		}
		ImGui::TreePop();
	}
}

void Node::setAppliedTransform(DirectX::FXMMATRIX transform) noexcept
{
	DirectX::XMStoreFloat4x4(&appliedTransform, transform);
}

DirectX::XMFLOAT4X4 Node::getAppliedTransform() 
{
	return appliedTransform;
}

int Node::getId() const noexcept
{
	return id;
}

class ModelControlWindow
{
public:
	void spawn(const Node& root) noexcept
	{
		if (ImGui::Begin("Model"))
		{
			ImGui::Columns(2, nullptr, true);
			root.spawnControlTree(selectedNode);

			ImGui::NextColumn();
			if (selectedNode != nullptr)
			{
				const auto id = selectedNode->getId();
				auto iter = transforms.find(id);
				if (iter == transforms.end())
				{
					const auto& appliedTransform = selectedNode->getAppliedTransform();
					const auto angles = extractRollPitchYaw(appliedTransform);
					const auto translation = extractTranslation(appliedTransform);
					TransformParameters params;
					params.pitch = angles.x;
					params.yaw = angles.y;
					params.roll = angles.z;
					params.x = translation.x;
					params.y = translation.y;
					params.z = translation.z;
					const auto inserted = transforms.insert({ id, params });
					iter = inserted.first;
				}
				auto& transform = iter->second;
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
		const auto& transform = transforms.at(selectedNode->getId());
		return DirectX::XMMatrixRotationRollPitchYaw(transform.pitch, transform.yaw, transform.roll) *
			DirectX::XMMatrixTranslation(transform.x, transform.y, transform.z);
	}

	Node* getSelectedNode() const noexcept
	{
		return selectedNode;
	}

private:
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

Model::LoadException::LoadException(int line, const char* file, std::string note) noexcept : BaseException(line, file), note(std::move(note))
{
}

const char* Model::LoadException::what() const noexcept
{
	std::ostringstream oss;
	oss << BaseException::what() << std::endl << "[Note] " << getErrorNote();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Model::LoadException::getType() const noexcept
{
	return "Model Load Exception";
}

const std::string& Model::LoadException::getErrorNote() const noexcept
{
	return note;
}

Model::Model(const Renderer& renderer, const std::string& filePath, float scale) : controlWindow(std::make_unique<ModelControlWindow>())
{
	Assimp::Importer importer;
	const auto model = importer.ReadFile(filePath, aiProcess_Triangulate
		| aiProcess_JoinIdenticalVertices
		| aiProcess_ConvertToLeftHanded
		| aiProcess_GenNormals
		| aiProcess_CalcTangentSpace);

	if (model == nullptr)
	{
		throw Model::LoadException(__LINE__, __FILE__, importer.GetErrorString());
	}

	for (size_t i = 0; i < model->mNumMeshes; i++)
	{
		meshes.push_back(parseMesh(renderer, *model->mMeshes[i], model->mMaterials, filePath, scale));
	}

	int nextId = 0;
	root = parseNode(nextId, *model->mRootNode);
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

void Model::setTransform(DirectX::FXMMATRIX transform) noexcept
{
	root->setAppliedTransform(transform);
}

std::unique_ptr<Mesh> Model::parseMesh(
	const Renderer& renderer, 
	const aiMesh& mesh, 
	const aiMaterial* const* materials, 
	const std::filesystem::path& path, 
	float scale
) const noexcept
{
	VertexBufferData vertexBufferData(std::move(VertexLayout()
		.append(VertexLayout::ElementType::POSITION3D)
		.append(VertexLayout::ElementType::NORMAL)
		.append(VertexLayout::ElementType::TEXTURE2D)
		.append(VertexLayout::ElementType::TANGENT)
		.append(VertexLayout::ElementType::BITANGENT)));

	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		vertexBufferData.emplaceBack(
			DirectX::XMFLOAT3(mesh.mVertices[i].x * scale, mesh.mVertices[i].y * scale, mesh.mVertices[i].z * scale),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mNormals[i]),
			*reinterpret_cast<DirectX::XMFLOAT2*>(&mesh.mTextureCoords[0][i]),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mTangents[i]),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mBitangents[i])
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

	std::vector<std::shared_ptr<Bindable>> bindables;

	const auto rootPath = path.parent_path().string() + "\\";

	bool hasDiffuseMap = false;
	bool hasDiffuseAlpha = false;
	bool hasNormalMap = false;
	bool hasSpecularMap = false;
	bool hasSpecularAlpha = false;
	float shininess = 2.0f;
	DirectX::XMFLOAT3 diffuseColor = { 0.45f, 0.45f, 0.85f };
	DirectX::XMFLOAT3 specularColor = { 0.18f, 0.18f, 0.18f };
	if (mesh.mMaterialIndex >= 0)
	{
		auto& material = *materials[mesh.mMaterialIndex];
		aiString textureFileName;

		if (material.GetTexture(aiTextureType_DIFFUSE, 0, &textureFileName) == aiReturn_SUCCESS) {
			const auto diffuseMap = BindableStore::resolve<Texture>(renderer, rootPath + textureFileName.C_Str());
			bindables.push_back(diffuseMap);
			hasDiffuseMap = true;
			hasDiffuseAlpha = diffuseMap->hasAlpha();
		}

		if (material.GetTexture(aiTextureType_NORMALS, 0, &textureFileName) == aiReturn_SUCCESS) {
			bindables.push_back(BindableStore::resolve<Texture>(renderer, rootPath + textureFileName.C_Str(), 1));
			hasNormalMap = true;
		}

		if (material.GetTexture(aiTextureType_SPECULAR, 0, &textureFileName) == aiReturn_SUCCESS) {
			const auto specularMap = BindableStore::resolve<Texture>(renderer, rootPath + textureFileName.C_Str(), 2);
			bindables.push_back(specularMap);
			hasSpecularMap = true;
			hasSpecularAlpha = specularMap->hasAlpha();
		}

		material.Get(AI_MATKEY_COLOR_DIFFUSE, reinterpret_cast<aiColor3D&>(diffuseColor));
		material.Get(AI_MATKEY_COLOR_SPECULAR, reinterpret_cast<aiColor3D&>(specularColor));
		material.Get(AI_MATKEY_SHININESS, shininess);
		bindables.push_back(std::make_shared<Sampler>(renderer));
	}

	bindables.push_back(std::make_shared<VertexBuffer>(renderer, vertexBufferData));
	bindables.push_back(std::make_shared<IndexBuffer>(renderer, indices));

	auto vertexShader = BindableStore::resolve<VertexShader>(renderer, "phong_mesh_vertex.cso");
	auto vertexShaderBytecode = vertexShader->getBytecode();
	bindables.push_back(std::move(vertexShader));


	bindables.push_back(BindableStore::resolve<PixelShader>(renderer, "phong_mesh_pixel.cso"));
	
	struct ConstantData
	{
		DirectX::XMFLOAT3 materialColor;
		BOOL hasDiffuse;
		BOOL hasNormal;
		DirectX::XMFLOAT3 specularIntensity;
		BOOL hasSpecular;
		BOOL hasSpecularAlpha;
		float specularShininess;
		float padding[1];
	} constData;
	constData.materialColor = diffuseColor;
	constData.hasDiffuse = hasDiffuseMap;
	constData.hasNormal = hasNormalMap;
	constData.specularIntensity = specularColor;
	constData.hasSpecular = hasSpecularMap;
	constData.hasSpecularAlpha = hasSpecularAlpha;
	constData.specularShininess = shininess;
	bindables.push_back(std::make_shared<PixelConstantBuffer<ConstantData>>(renderer, constData));

	bindables.push_back(BindableStore::resolve<InputLayout>(renderer, vertexBufferData.getLayout(), vertexShaderBytecode));
	bindables.push_back(BindableStore::resolve<Rasterizer>(renderer, hasDiffuseAlpha));

	return std::make_unique<Mesh>(renderer, std::move(bindables));
}

std::unique_ptr<Node> Model::parseNode(int& nextId, const aiNode& node) const noexcept
{
	const auto transform = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&node.mTransformation)));

	std::vector<Mesh*> currentMeshes;
	currentMeshes.reserve(node.mNumMeshes);
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		const auto meshIndex = node.mMeshes[i];
		currentMeshes.push_back(meshes.at(meshIndex).get());
	}

	auto parsedNode = std::make_unique<Node>(nextId++, node.mName.C_Str(), std::move(currentMeshes), transform);
	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		parsedNode->addChild(parseNode(nextId, *node.mChildren[i]));
	}

	return parsedNode;
}