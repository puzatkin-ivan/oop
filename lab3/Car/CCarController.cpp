#include "stdafx.h"
#include "CCarController.h"

CCarController::CCarController(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "Info", std::bind(&CCarController::Info, this, std::placeholders::_1) },
		  { "EngineOn", std::bind(&CCarController::EngineOn, this, std::placeholders::_1) },
		  { "EngineOff", std::bind(&CCarController::EngineOff, this, std::placeholders::_1) },
		  { "SetGear", std::bind(&CCarController::SetGear, this, std::placeholders::_1) },
		  { "SetSpeed", std::bind(&CCarController::SetSpeed, this, std::placeholders::_1) } })
{
}

bool CCarController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strstream(commandLine);
	std::string action;
	strstream >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strstream);
		return true;
	}
	return false;
}

void CCarController::Info(std::istream& input)
{
	std::string statusEngine = m_car.IsEngineTurnOn() ? "on" : "off";

	m_output << "Engine is turned " + statusEngine << std::endl;
	m_output << "Gear is " << static_cast<int>(m_car.GetGear()) << std::endl;
	m_output << "Direction is " << static_cast<int>(m_car.GetDirection()) << std::endl;
	m_output << "Speed is " << m_car.GetSpeed() << std::endl;
}

void CCarController::EngineOn(std::istream& input)
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine was turned on" << std::endl;
	}
	else
	{
		m_output << "Engine is already turned on" << std::endl;
	}
}

void CCarController::EngineOff(std::istream& input)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine was turned off" << std::endl;
		return;
	}
	if (m_car.GetGear() != Gear::Neutral || m_car.GetSpeed() != 0)
	{
		m_output << "Engine was not turned off" << std::endl;
		return;
	}
	m_output << "Engine is already turned off" << std::endl;
}

void CCarController::SetGear(std::istream& input)
{
	if (!m_car.IsEngineTurnOn())
	{
		m_output << "Error: Engine was not turned on" << std::endl;
		return;
	}
	int gear;
	input >> gear;
	if (!m_car.SetGear(static_cast<Gear>(gear)))
	{
		m_output << "Gear wasn't change" << std::endl;
		return;
	}
	m_output << "Gear was change" << std::endl;
}

void CCarController::SetSpeed(std::istream& input)
{
	if (m_car.IsEngineTurnOn())
	{
		int speed;
		input >> speed;
		if (m_car.SetSpeed(speed))
		{
			m_output << "Speed was change" << std::endl;
			return;
		}
		m_output << "Speed wasn't change" << std::endl;
		return;
	}
	m_output << "Error: Engine was not turned on" << std::endl;
}
