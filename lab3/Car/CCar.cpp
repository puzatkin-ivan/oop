#include "stdafx.h"

#include "CCar.h"

CCar::CCar()
{
	m_isEngineTurnOn = false;
	m_speed = 0;
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
	if (!m_isEngineTurnOn || m_speed != 0 || m_gear != Gear::Neutral)
	{
		return false;
	}

	m_isEngineTurnOn = false;
	return true;
}

Direction CCar::GetDirection() const
{
	auto gear = static_cast<int>(m_gear);
	int movement = gear * m_speed;
	if (movement > 0)
	{
		return Direction::Forward;
	}
	else if (movement == 0 && m_speed == 0)
	{
		return Direction::None;
	}
	return Direction::Reverse;
}

unsigned CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (m_gear == Gear::Neutral && speed >= m_speed)
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
		return (m_speed == 0 && m_gear == Gear::Neutral) ? ChangeGearWithReverseGear(gear) : ChangeGearWithoutReverseGear(gear);
	}
	
	return false;
}

bool CCar::ChangeGearWithReverseGear(const Gear & gear)
{
	if (gear <= Gear::First)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool CCar::ChangeGearWithoutReverseGear(const Gear & gear)
{
	if (gear >= Gear::Neutral)
	{
		if (IsSpeedInSpeedRange(m_speed, GetSpeedRange(gear)))
		{
			m_gear = gear;
			return true;
		}
	}
	return false;
}

bool CCar::IsSpeedInSpeedRange(unsigned speed, const SpeedRange & range) const
{
	return (speed >= range.first && speed <= range.second);
}	

SpeedRange CCar::GetSpeedRange(const Gear & gear) const
{
	extern const std::map<Gear, SpeedRange> MapSpeed;
	auto it = MapSpeed.find(gear);
	return it->second;
}
