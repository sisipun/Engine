#ifndef BASE_THROW_MACROS
#define BASE_THROW_MACROS

#define BASE_THROW_NOINFO(hResult, hResultCall) if (FAILED(hResult = hResultCall)) { throw BaseHrException::BaseHrException(__LINE__, __FILE__, hResult); }
#define BASE_THROW_LAST_ERROR() throw BaseHrException::BaseHrException(__LINE__, __FILE__, GetLastError());


#endif