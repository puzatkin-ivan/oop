#pragma once
#include <vector>
#include <string>

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void Execute(std::istream& stream) = 0;
};

class ICreateShapeCommand : public ICommand
{
public:
	virtual ~ICreateShapeCommand() = default;
protected:
	virtual std::vector<std::string> GetParams(std::istream& input) = 0;
};
