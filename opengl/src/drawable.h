#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
};

#endif