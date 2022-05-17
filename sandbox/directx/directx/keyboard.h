#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <queue>
#include <bitset>
#include <optional>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			PRESS,
			RELEASE
		};

		Event(Type type, unsigned char code) noexcept : type(type), code(code)
		{
		}

		bool isPress() const noexcept
		{
			return type == Type::PRESS;
		}

		bool isRelease() const noexcept
		{
			return type == Type::RELEASE;
		}

		unsigned char getCode() const noexcept
		{
			return code;
		}

	private:
		Type type;
		unsigned char code;
	};

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard operator=(const Keyboard&) = delete;

	bool keyIsPressed(unsigned char keyCode) const noexcept;
	std::optional<Event> readKey() noexcept;
	bool keyIsEmpty() const noexcept;
	void clearKey() noexcept;

	std::optional<char> readChar() noexcept;
	bool charIsEmpty() const noexcept;
	void clearChar() noexcept;

	void clear() noexcept;

	void enableAutorepeat() noexcept;
	void disableAutorepeat() noexcept;
	bool autorepeatIsEnabled() const noexcept;

private:
	void onKeyPressed(unsigned char keyCode) noexcept;
	void onKeyReleased(unsigned char keyCode) noexcept;
	void onChar(char character) noexcept;
	void clearState() noexcept;
	template<typename T>
	static void trimBuffer(std::queue<T>& buffer) noexcept;

	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};

#endif