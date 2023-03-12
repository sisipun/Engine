#ifndef PICKLE_RENDERER
#define PICKLE_RENDERER

namespace pickle
{
    namespace renderer
    {
        enum class RendererType
        {
            DIRECT_X,
            OPEN_GL,
            METAL
        };

        class Renderer
        {
        public:
            Renderer(int width, int height);
            virtual ~Renderer();

            Renderer(const Renderer &renderer) = delete;
            Renderer &operator=(const Renderer &renderer) = delete;

            virtual void render() const = 0;

        protected:
            int width;
            int height;
        };
    }
}

#endif