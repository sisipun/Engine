#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>

#include "drawable_base.h"

class Mesh : public DrawableBase<Mesh>
{
public:
	Mesh(const Renderer& renderer, std::vector<std::unique_ptr<Bindable>> bindables) noexcept;

	void draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;

private:
	mutable DirectX::XMFLOAT4X4 transform;
};

class Node
{
	friend class Model;
	friend class ModelControlWindow;
public:
	Node(const std::string& name, std::vector<Mesh*> meshes, const DirectX::XMMATRIX& transform) noexcept;

	void draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept;
	void setAppliedTransform(DirectX::FXMMATRIX transform) noexcept;

private:
	void addChild(std::unique_ptr<Node> child) noexcept;
	void spawnControlTree(int& nodeIndex, std::optional<int>& selectedIndex, Node*& selectedNode) const noexcept;

	std::string name;
	std::vector<std::unique_ptr<Node>> children;
	std::vector<Mesh*> meshes;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};

class Model
{
public:
	Model(const Renderer& renderer, const std::string fileName) noexcept;
	~Model() noexcept;

	void draw(const Renderer& renderer) const noexcept;
	void spawnControlWindow() noexcept;

private:
	std::unique_ptr<Mesh> parseMesh(const Renderer& renderer, const aiMesh& mesh) const noexcept;
	std::unique_ptr<Node> parseNode(const aiNode& node) const noexcept;

private:
	std::unique_ptr<Node> root;
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::unique_ptr<class ModelControlWindow> controlWindow;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};

#endif
