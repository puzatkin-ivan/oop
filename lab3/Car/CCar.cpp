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
	bool isGearNeutral = (m_gear == Gear::Neutral && speed >= std::abs(m_speed));
	bool isSpeedOutOfRange = (IsSpeedInSpeedRange(speed, GetSpeedRange(m_gear)));

	if (isGearNeutral || !isSpeedOutOfRange)
	{
		return false;
	}

	bool isSpeedCanChange = (m_gear == Gear::Reverse || m_speed < 0);

	m_speed = (isSpeedCanChange) ? -speed : speed;
	return true;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(Gear gear)
{
	const bool isGearOutOfRange = gear < Gear::Reverse || gear > Gear::Fifth;
	const auto currentDirection = GetDirection();
	const bool notAllowSetGearReverseWhenDrivingReverse = currentDirection == Direction::Reverse 
		&& gear != Gear::Neutral && m_gear != Gear::Reverse;
	const bool notAllowSetGearReverseWhenDrivingForward = currentDirection == Direction::Forward && gear == Gear::Reverse;
	const bool isSpeedInRange = IsSpeedInSpeedRange(m_speed, GetSpeedRange(gear));
	
	if (!m_isEngineTurnedOn || isGearOutOfRange || notAllowSetGearReverseWhenDrivingReverse
		|| notAllowSetGearReverseWhenDrivingForward || !isSpeedInRange)
	{
		return false;
	}

	m_gear = gear;
	return true;
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
