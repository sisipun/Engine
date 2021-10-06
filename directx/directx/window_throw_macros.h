#ifndef WINDOW_THROW_MACROS_H
#define WINDOW_THROW_MACROS_H

#define WINDOW_THROW_LAST_ERROR() throw Window::HrException(__LINE__, __FILE__, GetLastError());
#define WINDOW_THROW_NO_RENDERER() throw Window::NoRendererException(__LINE__, __FILE__);

#endif