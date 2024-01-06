#ifndef PICKLE_RENDERER_CAMERA
#define PICKLE_RENDERER_CAMERA

#include <pickle/math.h>

namespace pickle
{
    namespace renderer
    {
        class Camera
        {
        public:
            Camera(math::Vector<3, float> cameraPosition, math::Vector<3, float> lookAtPosition);
            virtual ~Camera();

            Camera(const Camera &renderer) = delete;
            Camera &operator=(const Camera &renderer) = delete;

            math::Matrix<4, 4, float> getView() const;
            math::Vector<3, float> getPosition() const;

        private:
            math::Vector<3, float> cameraPosition;
            math::Vector<3, float> lookAtPosition;
        };
    }
}

#endif