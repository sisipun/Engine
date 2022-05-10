#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(std::string path) : vertices(), faces()
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

            std::vector<float> vertex(3);
            stream >> vertex[0] >> vertex[1] >> vertex[2];

            vertices.push_back(vertex);
        }
        else if (!line.compare(0, 2, "f "))
        {
            stream >> trash;

            int id, texId, normId;
            std::vector<int> face;
            while (stream >> id >> trash >> texId >> trash >> normId)
            {
                id--;
                face.push_back(id);
            }

            faces.push_back(face);
        }
    }

    std::cout << "Faces: " << faces.size() << ". Vertices: " << vertices.size();
}

std::vector<float> Model::getVertex(int i) const
{
    return vertices[i];
}

std::vector<int> Model::getFace(int i) const
{
    return faces[i];
}

int Model::getVerticesCount() const
{
    return vertices.size();
}

int Model::getFacesCount() const
{
    return faces.size();
}