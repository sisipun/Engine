#ifndef SURFACE_H
#define SURFACE_H

#include <string>
#include <memory>
#include <optional>

#include <DirectXTex\DirectXTex.h>

#include "win_api.h"
#include "base_hr_exception.h"

class Surface
{
public:
	class Color
	{
	public:
		constexpr Color() noexcept : value()
		{
		}

		constexpr Color(unsigned int value) noexcept : value(value)
		{
		}

		constexpr Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) noexcept : value((a << 24) | (r << 16) | (g << 8) | b)
		{
		}

		constexpr Color(unsigned char r, unsigned char g, unsigned char b) noexcept : value((255 << 24) | (r << 16) | (g << 8) | b)
		{
		}

		constexpr Color(Color color, unsigned char a) noexcept : value((a << 24) | color.value)
		{
		}

		Color& operator=(Color color) noexcept
		{
			value = color.value;
			return *this;
		}

		constexpr unsigned char getA() const noexcept
		{
			return value >> 24;
		}

		constexpr unsigned char getR() const noexcept
		{
			return (value >> 16) & 0xFF;
		}

		constexpr unsigned char getG() const noexcept
		{
			return (value >> 8) & 0xFF;
		}

		constexpr unsigned char getB() const noexcept
		{
			return value & 0xFF;
		}

		void setA(unsigned char a) noexcept
		{
			value = (value & 0xFFFFFF) | (a << 24);
		}

		void setR(unsigned char r) noexcept
		{
			value = (value & 0xFF00FFFF) | (r << 16);
		}

		void setG(unsigned char g) noexcept
		{
			value = (value & 0xFFFF00FF) | (g << 8);
		}

		void setB(unsigned char b) noexcept
		{
			value = (value & 0xFFFFFF00) | b;
		}

		unsigned int value;
	};

	class HrException : public BaseHrException
	{
	public:
		HrException(int line, const char* file, std::string node, HRESULT hResult) noexcept;
		HrException(int line, const char* file, std::string filename, std::string node, HRESULT hResult) noexcept;
		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		const std::string& getNote() const noexcept;
	private:
		std::optional<HRESULT> hResult;
		std::string note;
	};

	Surface(unsigned int width, unsigned int height);
	Surface(Surface&& source) noexcept = default;
	Surface(Surface& source) = delete;
	Surface& operator=(Surface&& source) noexcept = default;
	Surface& operator=(const Surface& source) = delete;
	~Surface() = default;
	void clear(Color fillValue) noexcept;
	void putPixel(unsigned int x, unsigned int y, Color color) noexcept;
	Color getPixel(unsigned int x, unsigned int y) const noexcept;
	unsigned int getWidth() const noexcept;
	unsigned int getHeight() const noexcept;
	Color* getBufferPointer() noexcept;
	const Color* getBufferPointer() const noexcept;
	const Color* getBufferPointerConst() const noexcept;
	static Surface fromFile(const std::string& filename);
	void save(const std::string& filename) const;
	bool isAlphaLoaded() const noexcept;

private:
	Surface(DirectX::ScratchImage scratch) noexcept;

	static constexpr DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	DirectX::ScratchImage scratch;
};

#endif