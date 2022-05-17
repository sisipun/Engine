#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <glm/glm.hpp>

#include "../bindable.h"
#include "../drawable.h"
#include "mesh.h"

class Model : public Bindable, public Drawable
{
public:
    Model() : Model(std::vector<Mesh>())
    {
    }

    Model(Mesh mesh) : Model(std::vector<Mesh>{mesh})
    {
    }

    Model(std::vector<Mesh> meshes) : meshes(meshes), transform(glm::mat4(1.0f))
    {
    }

    void bind(const Shader &shader) const override;

    void draw() const override;

    glm::mat4 transform;

protected:
    std::vector<Mesh> meshes;
};

#endif