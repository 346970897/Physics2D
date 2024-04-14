#include "RectangleShape.h"

RectangleShape::RectangleShape(const double halfWidth, const double halfHeight)
{
	m_shapeType = ShapeType::RECTANGLE_SHAPE;
	m_halfWidth = halfWidth;
	m_halfHeight = halfHeight;

	for (int i = 0; i < 4; i++)
	{
		double x = i == 0 || i == 3 ? m_halfWidth : -m_halfWidth;
		double y = i < 2 ? m_halfHeight : -m_halfHeight;
		m_vertices.push_back(PhysicsVector(x, y, 0));
	}
}

RectangleShape::~RectangleShape()
{
}

std::vector<PhysicsVector> RectangleShape::GetVertices() const
{
	return m_vertices;
}

double RectangleShape::width()
{
	return m_halfWidth * 2;
}

double RectangleShape::height()
{
	return m_halfHeight * 2;
}

void RectangleShape::GetAABB(PhysicsVector& min, PhysicsVector& max)
{
	min.x() = -m_halfWidth;
	min.y() = -m_halfHeight;
	max.x() = m_halfWidth;
	max.y() = m_halfHeight;
}

double RectangleShape::GetArea()
{
	return 4 * m_halfWidth * m_halfHeight;
}


