#include "stdafx.h"
#include "CCarControl.h"

CCarControl::CCarControl(CCar & car, std::istream & input, std::ostream & output)
	:m_car(car)
	,m_input(input)
	,m_output(output)
	,m_actionMap({
		{ "Info", std::bind(&CCarControl::Info, this, std::placeholders::_1) }
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