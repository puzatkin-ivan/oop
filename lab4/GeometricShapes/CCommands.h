#pragma once
#include <memory>
#include "ICommand.h"
#include "CPoint.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"

class CCreateShapeCommand : virtual public ICreateShapeCommand
{
protected:
	std::vector<std::string> GetParams(std::istream& input) override;
};

class CAddLineSegmentCommand : public CCreateShapeCommand
{
public:
	CAddLineSegmentCommand(std::vector<std::unique_ptr<IShape>>& shapes);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
};

class CAddCircleCommand : public CCreateShapeCommand
{
public:
	CAddCircleCommand(std::vector<std::unique_ptr<IShape>>& shapes);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
};

class CAddRectangleCommand : public CCreateShapeCommand
{
public:
	CAddRectangleCommand(std::vector<std::unique_ptr<IShape>>& shapes);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
};

class CAddTriangleCommand : public CCreateShapeCommand
{
public:
	CAddTriangleCommand(std::vector<std::unique_ptr<IShape>>& shapes);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
};

class CPrintInfoCommand : public ICommand
{
public:
	CPrintInfoCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
	std::ostream& m_output;
};

class CPrintMinPerimeterCommand : public ICommand
{
public:
	CPrintMinPerimeterCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
	std::ostream& m_output;
};

class CPrintMaxAreaCommand : public ICommand
{
public:
	CPrintMaxAreaCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::ostream& output);
	void Execute(std::istream& input) override;
private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
	std::ostream& m_output;
};
