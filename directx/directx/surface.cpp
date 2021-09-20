#define FULL_WINTARD

#include <algorithm>
#include <sstream>

#include "surface.h"

namespace Gdiplus
{
using std::min;
using std::max;
}
#include <gdiplus.h>

#pragma comment( lib,"gdiplus.lib" ) // TODO remove

Surface::Surface(unsigned int width, unsigned int height, unsigned int pitch) noexcept :
	buffer(std::make_unique<Color[]>(pitch* height)),
	width(width),
	height(height)
{
}

Surface& Surface::operator=(Surface&& source) noexcept
{
	width = source.width;
	height = source.height;
	buffer = std::move(source.buffer);
	source.buffer = nullptr;
	return *this;
}

Surface::Surface(unsigned int width, unsigned int height) noexcept
	:
	Surface(width, height, width)
{
}

Surface::Surface(Surface&& source) noexcept
	:
	buffer(std::move(source.buffer)),
	width(source.width),
	height(source.height)
{
}

Surface::~Surface()
{
}

void Surface::clear(Color fillValue) noexcept
{
	memset(buffer.get(), fillValue.value, width * height * sizeof(Color));
}

void Surface::putPixel(unsigned int x, unsigned int y, Color color) noexcept
{
	buffer[y * width + x] = color;
}

Surface::Color Surface::getPixel(unsigned int x, unsigned int y) const noexcept
{
	return buffer[y * width + x];
}

unsigned int Surface::getWidth() const noexcept
{
	return width;
}

unsigned int Surface::getHeight() const noexcept
{
	return height;
}

Surface::Color* Surface::getBufferPointer() noexcept
{
	return buffer.get();
}

const Surface::Color* Surface::getBufferPointer() const noexcept
{
	return buffer.get();
}

const Surface::Color* Surface::getBufferPointerConst() const noexcept
{
	return buffer.get();
}

Surface Surface::fromFile(const std::string& filename)
{
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int pitch = 0;
	std::unique_ptr<Color[]> pBuffer = nullptr;

	wchar_t wideName[512];
	mbstowcs_s(nullptr, wideName, filename.c_str(), _TRUNCATE);

	Gdiplus::Bitmap bitmap(wideName);
	if (bitmap.GetLastStatus() != Gdiplus::Status::Ok)
	{
		std::stringstream ss;
		ss << "Loading image [" << filename << "]: failed to load.";
		throw Exception(__LINE__, __FILE__, ss.str());
	}

	height = bitmap.GetHeight();
	pBuffer = std::make_unique<Color[]>(width * height);

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			Gdiplus::Color color;
			bitmap.GetPixel(x, y, &color);
			pBuffer[y * pitch + x] = color.GetValue();
		}
	}

	return Surface(width, height, std::move(pBuffer));
}

void Surface::save(const std::string& filename) const
{
	auto GetEncoderClsid = [&filename](const WCHAR* format, CLSID* clsId) -> void
	{
		UINT num = 0;
		UINT size = 0;

		Gdiplus::ImageCodecInfo* imageCodecInfo = nullptr;

		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0)
		{
			std::stringstream ss;
			ss << "Saving surface to [" << filename << "]: failed to get encoder; size == 0.";
			throw Exception(__LINE__, __FILE__, ss.str());
		}

		imageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (imageCodecInfo == nullptr)
		{
			std::stringstream ss;
			ss << "Saving surface to [" << filename << "]: failed to get encoder; failed to allocate memory.";
			throw Exception(__LINE__, __FILE__, ss.str());
		}

		GetImageEncoders(num, size, imageCodecInfo);

		for (UINT j = 0; j < num; ++j)
		{
			if (wcscmp(imageCodecInfo[j].MimeType, format) == 0)
			{
				*clsId = imageCodecInfo[j].Clsid;
				free(imageCodecInfo);
				return;
			}
		}

		free(imageCodecInfo);
		std::stringstream ss;
		ss << "Saving surface to [" << filename <<
			"]: failed to get encoder; failed to find matching encoder.";
		throw Exception(__LINE__, __FILE__, ss.str());
	};

	CLSID bmpID;
	GetEncoderClsid(L"image/bmp", &bmpID);

	wchar_t wideName[512];
	mbstowcs_s(nullptr, wideName, filename.c_str(), _TRUNCATE);

	Gdiplus::Bitmap bitmap(width, height, width * sizeof(Color), PixelFormat32bppARGB, (BYTE*)buffer.get());
	if (bitmap.Save(wideName, &bmpID, nullptr) != Gdiplus::Status::Ok)
	{
		std::stringstream ss;
		ss << "Saving surface to [" << filename << "]: failed to save.";
		throw Exception(__LINE__, __FILE__, ss.str());
	}
}

void Surface::copy(const Surface& source) noexcept
{
	memcpy(buffer.get(), source.buffer.get(), width * height * sizeof(Color));
}

Surface::Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> bufferParam) noexcept
	:
	width(width),
	height(height),
	buffer(std::move(bufferParam))
{
}

Surface::Exception::Exception(int line, const char* file, std::string note) noexcept : BaseException(line, file), note(std::move(note))
{
}

const char* Surface::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << BaseException::what() << std::endl << "[Note] " << getNote();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Surface::Exception::getType() const noexcept
{
	return "Graphics Exception";
}

const std::string& Surface::Exception::getNote() const noexcept
{
	return note;
}