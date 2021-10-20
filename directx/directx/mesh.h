#ifndef MESH_H
#define MESH_H

#include <assimp/scene.h>

#include "drawable.h"

class Mesh : public Drawable
{
public:
	Mesh(const Renderer& renderer, std::vector<std::shared_ptr<Bindable>> bindables) noexcept;

	void draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept;
	DirectX::XMMATRIX getTransform() const noexcept override;

private:
	mutable DirectX::XMFLOAT4X4 transform;
};

class Node
{
	friend class Model;
public:
	Node(int id, const std::string& name, std::vector<Mesh*> meshes, const DirectX::XMMATRIX& transform) noexcept;

	void draw(const Renderer& renderer, DirectX::FXMMATRIX accumulatedTransform) const noexcept;
	void setAppliedTransform(DirectX::FXMMATRIX transform) noexcept;
	void spawnControlTree(Node*& selectedNode) const noexcept;
	int getId() const noexcept;

private:
	void addChild(std::unique_ptr<Node> child) noexcept;

	int id;
	std::string name;
	std::vector<std::unique_ptr<Node>> children;
	std::vector<Mesh*> meshes;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};

class Model
{
public:
	class LoadException : public BaseException
	{
	public:
		LoadException(int line, const char* file, std::string note) noexcept;
		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		const std::string& getErrorNote() const noexcept;
	private:
		std::string note;
	};
	Model(const Renderer& renderer, const std::string fileName);
	~Model() noexcept;

	void draw(const Renderer& renderer) const noexcept;
	void spawnControlWindow() noexcept;

private:
	std::unique_ptr<Mesh> parseMesh(const Renderer& renderer, const aiMesh& mesh, const aiMaterial* const* materials) const noexcept;
	std::unique_ptr<Node> parseNode(int &nextId, const aiNode& node) const noexcept;

private:
	std::unique_ptr<Node> root;
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::unique_ptr<class ModelControlWindow> controlWindow;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};

#endif
