#include "keyboard.h"

bool Keyboard::keyIsPressed(unsigned char keyCode) const noexcept
{
	return keyStates[keyCode];
}

std::optional<Keyboard::Event> Keyboard::readKey() noexcept
{
	if (keyIsEmpty())
	{
		return std::nullopt;
	}

	Keyboard::Event event = keyBuffer.front();
	keyBuffer.pop();
	return std::optional(event);
}

bool Keyboard::keyIsEmpty() const noexcept
{
	return keyBuffer.empty();
}

std::optional<char> Keyboard::readChar() noexcept
{
	if (charIsEmpty())
	{
		return std::nullopt;
	}

	char character = charBuffer.front();
	charBuffer.pop();
	return character;
}

bool Keyboard::charIsEmpty() const noexcept
{
	return charBuffer.empty();
}

void Keyboard::clearKey() noexcept
{
	keyBuffer = std::queue<Event>();
}

void Keyboard::clearChar() noexcept
{
	charBuffer = std::queue<char>();
}

void Keyboard::clear() noexcept
{
	clearKey();
	clearChar();
}

void Keyboard::enableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::disableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::autorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::onKeyPressed(unsigned char keyCode) noexcept
{
	keyStates[keyCode] = true;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::PRESS, keyCode));
	trimBuffer(keyBuffer);
}

void Keyboard::onKeyReleased(unsigned char keyCode) noexcept
{
	keyStates[keyCode] = false;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::RELEASE, keyCode));
	trimBuffer(keyBuffer);
}

void Keyboard::onChar(char character) noexcept
{
	charBuffer.push(character);
	trimBuffer(charBuffer);
}

void Keyboard::clearState() noexcept
{
	keyStates.reset();
}

template<typename T>
void Keyboard::trimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}