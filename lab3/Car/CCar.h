#pragma once
#include "sheet.h"

class CCar
{
public:
	CCar();
	bool IsEngineTurnOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();

	Direction GetDirection() const;

	unsigned GetSpeed() const;
	bool SetSpeed(unsigned speed);

	Gear GetGear() const;
	bool SetGear(const Gear & gear);
private:
	bool IsSpeedInSpeedRange(unsigned speed, const SpeedRange & range);
	SpeedRange GetSpeedRange(const Gear & gear);
	bool IsChangesGearWithReverse(const Gear & gear);
	bool IsChangesGearWithoutReverse(const Gear & gear);
	Direction SetDirection(const Gear & gear);

	bool m_isEngineTurnOn;
	unsigned m_speed;
	Direction m_direction;
	Gear m_gear;
};