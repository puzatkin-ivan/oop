#pragma once
#include <map>
#include <functional>
#include "CCar.h"

using ActionMap = std::map<std::string, std::function<void(std::istream & args)>>;

class CCarController
{
public:
	CCarController(CCar & car, std::istream & input, std::ostream & output);
	bool HandleCommand();
private:
	void Info(std::istream & input);
	void EngineOn(std::istream & input);
	void EngineOff(std::istream & input);
	void SetGear(std::istream & input);
	void SetSpeed(std::istream & input);
	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;
	ActionMap m_actionMap;
};