#include <pickle/model/model.h>

const std::vector<pickle::renderer::Mesh>& pickle::renderer::Model::getMeshes() const
{
    return meshes;
}