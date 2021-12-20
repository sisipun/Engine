#include "string_util.h"

std::wstring toWide(const std::string& narrow)
{
	wchar_t wide[512];
	mbstowcs_s(nullptr, wide, narrow.c_str(), _TRUNCATE);
	return wide;
}

std::string toNarrow(const std::wstring& wide)
{
	char narrow[512];
	wcstombs_s(nullptr, narrow, wide.c_str(), _TRUNCATE);
	return narrow;
}