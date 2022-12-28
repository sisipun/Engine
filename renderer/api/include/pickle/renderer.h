#ifndef PICKLE_RENDERER
#define PICKLE_RENDERER

namespace pickle
{
    namespace renderer
    {
        class Renderer
        {
        public:
            Renderer()
            {
            }

            virtual ~Renderer()
            {
            }

            Renderer(const Renderer &renderer) = delete;
            Renderer &operator=(const Renderer &renderer) = delete;

            virtual void render() const = 0;
        };
    }
}

#endif