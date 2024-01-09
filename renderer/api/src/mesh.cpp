#include <pickle/mesh.h>

pickle::renderer::Mesh::Mesh(std::vector<pickle::renderer::Vertex> vertices) : vertices(vertices)
{
}

const std::vector<pickle::renderer::Vertex>& pickle::renderer::Mesh::getVertices() const
{
    return vertices;
}