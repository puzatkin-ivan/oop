#pragma once

#include "CPoint.h"
#include "CSolidShape.h"
#include <array>

class CTriangle : public CSolidShape
{
public:
	CTriangle() = delete;
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, 
		const std::string& outlineColor, const std::string& fillColor);
	~CTriangle() = default;

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	void SetVertex1(const CPoint& vertex);

	CPoint GetVertex2() const;
	void SetVertex2(const CPoint& vertex);

	CPoint GetVertex3() const;
	void SetVertex3(const CPoint& vertex);
protected:
	void AppendAdditionalProperties(std::ostream& stream) const override;
private:
	std::array<CPoint, 3> m_vertices;
};
