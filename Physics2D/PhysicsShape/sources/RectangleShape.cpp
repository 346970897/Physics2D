#include "RectangleShape.h"

RectangleShape::RectangleShape(const double i_halfWidth, const double i_halfHeight)
{
	m_shapeType = ShapeType::RECTANGLE_SHAPE;
	m_halfWidth = i_halfWidth;
	m_halfHeight = i_halfHeight;

	for (int i = 0; i < 4; i++)
	{
		double x = i == 0 || i == 3 ? m_halfWidth : -m_halfWidth;
		double y = i < 2 ? m_halfHeight : -m_halfHeight;
		m_vertices.push_back(PhysicsVector2D(x, y));
	}
}

RectangleShape::~RectangleShape()
{
}

std::vector<PhysicsVector2D> RectangleShape::GetVertices() const
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

void RectangleShape::GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max)
{
	i_min.x() = -m_halfWidth;
	i_min.y() = -m_halfHeight;
	i_max.x() = m_halfWidth;
	i_max.y() = m_halfHeight;
}

double RectangleShape::GetArea()
{
	return 4 * m_halfWidth * m_halfHeight;
}


