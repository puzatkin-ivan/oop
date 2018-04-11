#pragma once
#include <map>
#include <utility>

using SpeedRange = std::pair<int, int>;

enum class Direction
{
	Reverse = -1,
	None = 0,
	Forward,
};

enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
};

class CCar
{
public:
	CCar();
	bool IsEngineTurnOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();

	Direction GetDirection() const;

	int GetSpeed() const;
	bool SetSpeed(int speed);

	Gear GetGear() const;
	bool SetGear(Gear gear);
private:
	static bool IsSpeedInSpeedRange(int speed, SpeedRange range);
	SpeedRange GetSpeedRange(Gear gear) const;

	bool m_isEngineTurnedOn;
	int m_speed;
	Gear m_gear;
};
