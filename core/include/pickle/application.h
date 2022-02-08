#ifndef PICKLE_APPLICATION
#define PICKLE_APPLICATION

#include <pickle/window.h>
namespace pickle
{
    class Application
    {
    public:
        Application();
        ~Application();

        Application(const Application &application) = delete;
        Application &operator=(const Application &application) = delete;

        void start();

    private:
        Window window;
    };
}

#endif
