#pragma once
#include <string>

struct Sportsman
{
	Sportsman() = default;
	Sportsman(const std::string& name, double height, double weight)
		:name(name)
		,height(height)
		,weight(weight)
	{

	}

	std::string name;
	double height;
	double weight;
};