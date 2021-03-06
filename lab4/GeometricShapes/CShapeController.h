#pragma once
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <fstream>
#include "IShape.h"
#include "CCommands.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

class CShapeController
{
public:
	CShapeController(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output);
	
	void Run(std::istream& stream);

	void AddItem(const std::string & shortcut, std::unique_ptr<ICommand> && command)
	{
		m_actionMap.emplace_back(shortcut, std::move(command));
	}
private:
	struct Item
	{
		Item(const std::string& shortcut, std::unique_ptr<ICommand>&& command)
			:shortcut(shortcut)
			,command(std::move(command))
		{
		}
		std::string shortcut;
		std::unique_ptr<ICommand> command;
	};

	using ActionMap = std::vector<Item>;
	ActionMap m_actionMap;
	std::vector<std::unique_ptr<IShape>>& m_shapes;
	std::ostream& m_output;
};
