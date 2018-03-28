#pragma once
#include <map>
#include <functional>
#include "CCar.h"

using ActionMap = std::map<std::string, std::function<bool(std::istream & args)>>;

class CCarControl
{
public:
	CCarControl(CCar & car, std::istream & input, std::ostream & output);
	bool HandleCommand();
private:
	bool Info(std::istream & input);
	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;
	const ActionMap m_actionMap;
};