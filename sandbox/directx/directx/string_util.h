#ifndef STRING_UTIL
#define STRING_UTIL

#include <string>

std::wstring toWide(const std::string& narrow);

std::string toNarrow(const std::wstring& wide);

#endif 
