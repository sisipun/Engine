#include <sstream>

#include "base_exception.h"

BaseException::BaseException(int line, const char* file) noexcept : line(line), file(file)
{
}

const char* BaseException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << std::endl << getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const const char* BaseException::getType() const noexcept
{
	return "Base Exception";
}

int BaseException::getLine() const noexcept
{
	return line;
}

const std::string& BaseException::getFile() const noexcept
{
	return file;
}

std::string BaseException::getOriginString() const noexcept {
	std::ostringstream oss;
	oss << "[FILE] " << file << std::endl << "[LINE] " << line;
	return oss.str();
}
