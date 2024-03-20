#include <pickle/model/mesh.h>

pickle::renderer::Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : vertices(vertices), indices(indices)
{
}

const std::vector<pickle::renderer::Vertex> &pickle::renderer::Mesh::getVertices() const
{
    return vertices;
}

const std::vector<unsigned int> &pickle::renderer::Mesh::getIndices() const
{
    return indices;
}