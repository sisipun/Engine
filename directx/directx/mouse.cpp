#include "mouse.h"
#include <Windows.h>

std::optional<Mouse::Event> Mouse::read() noexcept
{
	if (buffer.size() == 0)
	{
		return std::nullopt;
	}

	Mouse::Event event = buffer.front();
	buffer.pop();
	return event;
}

void Mouse::clear() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::onMouseMove(int x, int y) noexcept
{
	this->x = x;
	this->y = y;

	buffer.push(Mouse::Event(Mouse::Event::Type::MOVE, *this));
	trimBuffer();
}

void Mouse::onMouseLeave() noexcept
{
	inWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::LEAVE, *this));
	trimBuffer();
}

void Mouse::onMouseEnter() noexcept
{
	inWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::ENTER, *this));
	trimBuffer();
}

void Mouse::onLeftPressed(int x, int y) noexcept
{
	leftPressed = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::L_PRESS, *this, x, y));
	trimBuffer();
}

void Mouse::onLeftReleased(int x, int y) noexcept
{
	leftPressed = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::L_RELEASE, *this, x, y));
	trimBuffer();
}

void Mouse::onRightPressed(int x, int y) noexcept
{
	rightPressed = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::R_PRESS, *this, x, y));
	trimBuffer();
}

void Mouse::onRightReleased(int x, int y) noexcept
{
	rightPressed = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::R_RELEASE, *this, x, y));
	trimBuffer();
}

void Mouse::onWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WHEEL_UP, *this, x, y));
	trimBuffer();
}

void Mouse::onWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WHEEL_DOWN, *this, x, y));
	trimBuffer();
}

void Mouse::trimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

void Mouse::onWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		onWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		onWheelDown(x, y);
	}
}