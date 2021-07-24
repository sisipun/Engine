#ifndef MOUSE_H
#define MOUSE_H

#include <queue>
#include <optional>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			L_PRESS,
			L_RELEASE,
			R_PRESS,
			R_RELEASE,
			WHEEL_UP,
			WHEEL_DOWN,
			MOVE,
			ENTER,
			LEAVE
		};

		Event(Type type, const Mouse& parent) noexcept : Event(type, parent, parent.x, parent.y)
		{
		}

		Event(Type type, const Mouse& parent, int x, int y) noexcept : type(type), leftPressed(parent.leftPressed), rightPressed(parent.rightPressed), x(x), y(y)
		{
		}

		Type getType() const noexcept
		{
			return type;
		}

		std::pair<int, int> getPosition() const noexcept
		{
			return std::pair(x, y);
		}

		int getPositionX() const noexcept
		{
			return x;
		}

		int getPositionY() const noexcept
		{
			return y;
		}

		bool leftIsPressed() const noexcept
		{
			return leftPressed;
		}

		bool rightIsPressed() const noexcept
		{
			return rightPressed;
		}

	private:
		Type type;
		bool leftPressed;
		bool rightPressed;
		int x;
		int y;
	};

	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	std::pair<int, int> getPosition() const noexcept
	{
		return std::pair(x, y);
	}

	int getPositionX() const noexcept
	{
		return x;
	}

	int getPositionY() const noexcept
	{
		return y;
	}

	bool isInWindow() const noexcept
	{
		return inWindow;
	}

	bool leftIsPressed() const noexcept
	{
		return leftPressed;
	}

	bool rightIsPressed() const noexcept
	{
		return rightPressed;
	}

	bool isEmpty() const noexcept
	{
		return buffer.empty();
	}

	std::optional<Mouse::Event> read() noexcept;
	void clear() noexcept;

private:
	void onMouseMove(int x, int y) noexcept;
	void onMouseLeave() noexcept;
	void onMouseEnter() noexcept;
	void onLeftPressed(int x, int y) noexcept;
	void onLeftReleased(int x, int y) noexcept;
	void onRightPressed(int x, int y) noexcept;
	void onRightReleased(int x, int y) noexcept;
	void onWheelUp(int x, int y) noexcept;
	void onWheelDown(int x, int y) noexcept;
	void trimBuffer() noexcept;
	void onWheelDelta(int x, int y, int delta) noexcept;

	static constexpr unsigned int bufferSize = 16u;
	int x;
	int y;
	bool leftPressed = false;
	bool rightPressed = false;
	bool inWindow = false;
	int wheelDeltaCarry = 0;
	std::queue<Event> buffer;
};

#endif