#ifndef SURFACE_THROW_MACROS_H
#define SURFACE_THROW_MACROS_H

#define SURFACE_THROW_NOINFO(hResult, hResultCall, message) if (FAILED(hResult = hResultCall)) { throw Surface::HrException(__LINE__, __FILE__, message, hResult); }
#define SURFACE_FILE_THROW_NOINFO(hResult, hResultCall, filename, message) if (FAILED(hResult = hResultCall)) { throw Surface::HrException(__LINE__, __FILE__, filename, message, hResult); }

#endif