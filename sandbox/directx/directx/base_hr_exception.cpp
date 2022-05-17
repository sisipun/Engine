#include <sstream>

#include "base_hr_exception.h"

BaseHrException::BaseHrException(int line, const char* file, HRESULT hResult) noexcept : BaseException(line, file), hResult(hResult)
{
}

const char* BaseHrException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << std::endl << "[Error code] " << getErrorCode() << std::endl << "[Description] " << getErrorString() << std::endl << getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* BaseHrException::getType() const noexcept
{
	return "Window Exception";
}

HRESULT BaseHrException::getErrorCode() const noexcept
{
	return hResult;
}

std::string BaseHrException::getErrorString() const noexcept
{
	return translateErrorCode(hResult);
}


std::string BaseHrException::translateErrorCode(HRESULT hResult) noexcept
{
	char* msgBuf = nullptr;
	DWORD msgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hResult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgBuf),
		0,
		nullptr
	);
	if (msgLen == 0)
	{
		return "Undefined error code";
	}
	std::string errorString = msgBuf;
	LocalFree(msgBuf);
	return errorString;
}