#include "stdafx.h"

#include "CCar.h"

CCar::CCar()
{
	m_isEngineTurnOn = false;
	m_speed = 0;
	m_direction = Direction::None;
	m_gear = Gear::Neutral;
}

bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineTurnOn)
	{
		return false;
	}

	m_isEngineTurnOn = true;
	return true;	
}

bool CCar::TurnOffEngine()
{
	if (!m_isEngineTurnOn || GetSpeed() != 0 || GetGear() != Gear::Neutral)
	{
		return false;
	}

	m_isEngineTurnOn = false;
	return true;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

unsigned CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (m_gear == Gear::Neutral && speed >= GetSpeed())
	{
		return false;
	}
	if (IsSpeedInSpeedRange(speed, GetSpeedRange(m_gear)))
	{
		m_speed = speed;
		return true;
	}
	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(const Gear & gear)
{
	if (m_isEngineTurnOn)
	{
		return (m_speed == 0) ? IsChangesGearWithReverse(gear) : IsChangesGearWithoutReverse(gear);
	}
	
	return false;
}

bool CCar::IsChangesGearWithReverse(const Gear & gear)
{
	if (gear <= Gear::First)
	{
		m_gear = gear;
		m_direction = SetDirection(gear);
		return true;
	}
	return false;
}

bool CCar::IsChangesGearWithoutReverse(const Gear & gear)
{
	if (gear >= Gear::Neutral)
	{
		if (IsSpeedInSpeedRange(m_speed, GetSpeedRange(gear)))
		{
			m_direction = Direction::Forward;
			m_gear = gear;
			return true;
		}
	}
	return false;
}

bool CCar::IsSpeedInSpeedRange(unsigned speed, const SpeedRange & range)
{
	return (speed >= range.first && speed <= range.second);
}

SpeedRange CCar::GetSpeedRange(const Gear & gear)
{
	auto it = MapSpeed.find(gear);
	return it->second;
}

Direction CCar::SetDirection(const Gear & gear)
{
	auto numberGear = static_cast<int>(gear);
	if (numberGear > 0)
	{
		return Direction::Forward;
	}
	else if (numberGear < 0)
	{
		return Direction::Reverse;
	}
	else if (m_speed == 0)
	{
		return Direction::None;
	}
	return m_direction;
}