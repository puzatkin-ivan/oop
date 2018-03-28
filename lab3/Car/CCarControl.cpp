#include "stdafx.h"
#include "CCarControl.h"

CCarControl::CCarControl(CCar & car, std::istream & input, std::ostream & output)
	:m_car(car)
	,m_input(input)
	,m_output(output)
	,m_actionMap({
		{ "Info", std::bind(&CCarControl::Info, this, std::placeholders::_1) },
		{ "EngineOn", std::bind(&CCarControl::EngineOn, this, std::placeholders::_1) },
		{ "EngineOff", std::bind(&CCarControl::EngineOff, this, std::placeholders::_1) }
	})
{
}

bool CCarControl::HandleCommand()
{
	std::string action;
	std::getline(m_input, action);
	auto it = m_actionMap.find(action);
	
	return it != m_actionMap.end() ? it->second(m_input) : false;
}

bool CCarControl::Info(std::istream & input)
{
	std::string statusEngine = m_car.IsEngineTurnOn() ? "on" : "off";

	m_output << "Engine is turned " + statusEngine << std::endl;
	m_output << "Gear is " <<  static_cast<int>(m_car.GetGear()) << std::endl;
	m_output << "Direction is " << static_cast<int>(m_car.GetDirection()) << std::endl;
	m_output << "Speed is " << m_car.GetSpeed() << std::endl;
	return true;
}

bool CCarControl::EngineOn(std::istream & input)
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine was turned on" << std::endl;
		
	}
	else
	{
		m_output << "Engine is already turned on" << std::endl;
	}
	return true;
}

bool CCarControl::EngineOff(std::istream & input)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine was turned off" << std::endl;		
	}
	else if (m_car.GetGear() != Gear::Neutral || m_car.GetSpeed() != 0)
	{
		m_output << "Engine was not turned off" << std::endl;
	}
	else
	{
		m_output << "Engine is already turned off" << std::endl;
	}
	return true;
}