#ifndef BINDABLE_H
#define BINDABLE_H

#include "model/shader.h"

class Bindable
{
public:
    virtual ~Bindable() = default;
    virtual void bind(const Shader &shader) const = 0;
};

#endif