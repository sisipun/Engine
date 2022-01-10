#ifndef PICKLE_RENDERER
#define PICKLE_RENDERER

namespace pickle
{
    namespace renderer
    {
        class Renderer
        {
            public:
            virtual void render() const = 0;
        };
    }
}

#endif