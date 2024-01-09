#include <pickle/mesh.h>

pickle::renderer::Mesh::Mesh(const std::vector<Vertex> &vertices) : vertices(vertices)
{
}

const std::vector<pickle::renderer::Vertex> &pickle::renderer::Mesh::getVertices() const
{
    return vertices;
}
