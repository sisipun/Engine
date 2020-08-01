#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "body.h"

class RigidBody
{
public:
    RigidBody(Body body) : body(body)
    {
    }

    Body getBody()
    {
        return body;
    }

    void updateBody(float x, float y) {
        body.x = x;
        body.y = y;
    }

private:
    Body body;
};

#endif