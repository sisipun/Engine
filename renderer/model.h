#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

class Model
{
public:
    Model(std::string path);

    std::vector<float> getVertex(int i) const;
    std::vector<int> getFace(int i) const;

    int getVerticesCount() const;
    int getFacesCount() const;

private:
    std::vector<std::vector<float> > vertices;
    std::vector<std::vector<int> > faces;
};

#endif