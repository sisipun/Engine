#include <algorithm>
#include <sstream>
#include <filesystem>

#include "surface.h"
#include "surface_throw_macros.h"
#include "string_util.h"

Surface::Surface(unsigned int width, unsigned int height)
{
	HRESULT hResult;
	SURFACE_THROW_NOINFO(hResult, scratch.Initialize2D(format, width, height, 1, 1), "Failed to initialize ScratchImage");
}

void Surface::clear(Color fillValue) noexcept
{
	const int width = getWidth();
	const int height = getHeight();
	const DirectX::Image& imageData = *scratch.GetImage(0, 0, 0);
	for (size_t y = 0; y < height; y++)
	{
		Color* rowStart = reinterpret_cast<Color*>(imageData.pixels + imageData.rowPitch * y);
		std::fill(rowStart, rowStart + imageData.width, fillValue);
	}
}

void Surface::putPixel(unsigned int x, unsigned int y, Color color) noexcept
{
	const DirectX::Image& imageData = *scratch.GetImage(0, 0, 0);
	reinterpret_cast<Color*>(imageData.pixels + imageData.rowPitch * y)[x] = color;
}

Surface::Color Surface::getPixel(unsigned int x, unsigned int y) const noexcept
{
	const DirectX::Image& imageData = *scratch.GetImage(0, 0, 0);
	return reinterpret_cast<Color*>(imageData.pixels + imageData.rowPitch * y)[x];
}

unsigned int Surface::getWidth() const noexcept
{
	return (unsigned int)scratch.GetMetadata().width;
}

unsigned int Surface::getHeight() const noexcept
{
	return (unsigned int)scratch.GetMetadata().height;
}

Surface::Color* Surface::getBufferPointer() noexcept
{
	return reinterpret_cast<Color*>(scratch.GetPixels());
}

const Surface::Color* Surface::getBufferPointer() const noexcept
{
	return const_cast<Surface*>(this)->getBufferPointer();
}

const Surface::Color* Surface::getBufferPointerConst() const noexcept
{
	return const_cast<Surface*>(this)->getBufferPointer();
}

Surface Surface::fromFile(const std::string& filename)
{
	HRESULT hResult;

	DirectX::ScratchImage scratch;
	SURFACE_FILE_THROW_NOINFO(hResult, DirectX::LoadFromWICFile(toWide(filename).c_str(), DirectX::WIC_FLAGS_NONE, nullptr, scratch), filename, "Failed to load image");

	if (scratch.GetImage(0, 0, 0)->format != format)
	{
		DirectX::ScratchImage converted;
		SURFACE_FILE_THROW_NOINFO(hResult, DirectX::Convert(*scratch.GetImage(0, 0, 0), format, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, converted), filename, "Failed to convert image");
		return Surface(std::move(converted));
	}

	return Surface(std::move(scratch));
}

void Surface::save(const std::string& filename) const
{
	const auto getCodecId = [](const std::string& filename)
	{
		const std::filesystem::path path = filename;
		const auto extension = path.extension().string();
		if (extension == ".png")
		{
			return DirectX::WIC_CODEC_PNG;
		}
		else if (extension == ".jpg")
		{
			return DirectX::WIC_CODEC_JPEG;
		}
		else if (extension == ".bpm")
		{
			return DirectX::WIC_CODEC_BMP;
		}
		else
		{
			// TODO add exception for this case
			return DirectX::WIC_CODEC_PNG;
		}
	};

	HRESULT hResult;
	SURFACE_FILE_THROW_NOINFO(hResult, DirectX::SaveToWICFile(*scratch.GetImage(0, 0, 0), DirectX::WIC_FLAGS_NONE, GetWICCodec(getCodecId(filename)), toWide(filename).c_str()), filename, "Failed to save image");
}

bool Surface::isAlphaLoaded() const noexcept
{
	return !scratch.IsAlphaAllOpaque();
}

Surface::Surface(DirectX::ScratchImage scratch) noexcept : scratch(std::move(scratch))
{
}

Surface::HrException::HrException(int line, const char* file, std::string note, HRESULT hResult) noexcept :
	BaseHrException(line, file, hResult),
	note("[Error String] " + HrException::translateErrorCode(hResult) + "\n" + note)
{
}


Surface::HrException::HrException(int line, const char* file, std::string filename, std::string note, HRESULT hResult) noexcept :
	BaseHrException(line, file, hResult),
	note("[File] " + filename + "\n" + "[Note] " + "[Error String] " + HrException::translateErrorCode(hResult) + "\n" + note)
{
}

const char* Surface::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << BaseHrException::what() << std::endl << "[Note] " << getNote();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Surface::HrException::getType() const noexcept
{
	return "Graphics Exception";
}

const std::string& Surface::HrException::getNote() const noexcept
{
	return note;
}