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
	bool IsSpeedInSpeedRange(unsigned speed, const SpeedRange & range) const;
	SpeedRange GetSpeedRange(const Gear & gear) const;
	bool ChangeGearWithReverseGear(const Gear & gear);
	bool ChangeGearWithoutReverseGear(const Gear & gear);

	bool m_isEngineTurnOn;
	unsigned m_speed;
	Gear m_gear;
};