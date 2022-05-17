#include <pickle/model.h>

#include <fstream>
#include <iostream>
#include <sstream>

pickle::renderer::Model::Model(std::string path) : vertices(), faces()
{
    std::ifstream in(path);
    if (in.fail())
    {
        std::cout << "Can't open file: " << path << std::endl;
    }

    for (std::string line; std::getline(in, line);)
    {
        std::stringstream stream(line.c_str());

        char trash;
        if (!line.compare(0, 2, "v "))
        {
            stream >> trash;

            pickle::math::Vector<3, float> vertex;
            stream >> vertex.data[0] >> vertex.data[1] >> vertex.data[2];

            vertices.push_back(vertex);
        }
        if (!line.compare(0, 4, "vt  "))
        {
            stream >> trash;
            stream >> trash;

            pickle::math::Vector<3, float> textureCoord;
            stream >> textureCoord.data[0] >> textureCoord.data[1] >> textureCoord.data[2];

            textureCoords.push_back(textureCoord);
        }
        else if (!line.compare(0, 2, "f "))
        {
            stream >> trash;

            int id, texId, normId;
            pickle::math::Vector<9, int> face;
            for (int i = 0; i < 9; i += 3)
            {
                stream >> id >> trash >> texId >> trash >> normId;
                id--;
                texId--;
                normId--;

                face.data[i] = id;
                face.data[i + 1] = texId;
                face.data[i + 2] = normId;
            }

            faces.push_back(face);
        }
    }
}

pickle::math::Vector<3, float> pickle::renderer::Model::getVertex(int i) const
{
    return vertices[i];
}

pickle::math::Vector<3, float> pickle::renderer::Model::getTextureCoord(int i) const
{
    return textureCoords[i];
}

pickle::math::Vector<9, int> pickle::renderer::Model::getFace(int i) const
{
    return faces[i];
}

int pickle::renderer::Model::getVerticesCount() const
{
    return vertices.size();
}

int pickle::renderer::Model::getFacesCount() const
{
    return faces.size();
}