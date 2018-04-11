#include "stdafx.h"

#include "CCar.h"

static const std::map<Gear, SpeedRange> MapSpeed = {
	{ Gear::Reverse, { 0, 20 } },
	{ Gear::Neutral, { 0, 150 } },
	{ Gear::First, { 0, 30 } },
	{ Gear::Second, { 20, 50 } },
	{ Gear::Third, { 30, 60 } },
	{ Gear::Fourth, { 40, 90 } },
	{ Gear::Fifth, { 50, 150 } },
};

CCar::CCar()
	: m_isEngineTurnedOn(false)
	, m_speed(0)
	, m_gear(Gear::Neutral)
{
}

bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnedOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineTurnedOn)
	{
		return false;
	}

	m_isEngineTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isEngineTurnedOn || m_speed != 0 || m_gear != Gear::Neutral)
	{
		return false;
	}

	m_isEngineTurnedOn = false;
	return true;
}

Direction CCar::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	else if (m_speed < 0)
	{
		return Direction::Reverse;
	}
	return Direction::None;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

bool CCar::SetSpeed(int speed)
{
	if (m_gear == Gear::Neutral && speed >= std::abs(m_speed))
	{
		return false;
	}
	if (IsSpeedInSpeedRange(speed, GetSpeedRange(m_gear)))
	{
		if (m_gear == Gear::Reverse || m_speed < 0)
		{
			m_speed = -speed;
		}
		else
		{
			m_speed = speed;
		}
		return true;
	}
	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(Gear gear)
{
	if (m_isEngineTurnedOn)
	{
		if (gear == Gear::Reverse)
		{
			if (m_gear == Gear::Neutral && std::abs(m_speed) == 0)
			{
				m_gear = gear;
				return true;
			}
		}
		else if (IsSpeedInSpeedRange(m_speed, GetSpeedRange(gear)))
		{
			m_gear = gear;
			return true;
		}
	}

	return false;
}

bool CCar::IsSpeedInSpeedRange(int speed, SpeedRange range)
{
	speed = std::abs(speed);
	return (speed >= range.first && speed <= range.second);
}

SpeedRange CCar::GetSpeedRange(Gear gear) const
{
	auto it = MapSpeed.find(gear);
	return it->second;
}
