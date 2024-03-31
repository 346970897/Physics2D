#include "CircleShape.h"

CircleShape::CircleShape(const double i_radius): PhysicsShape()
{
	m_shapeType = ShapeType::CIRCLE_SHAPE;
	m_radius = i_radius;
}

CircleShape::~CircleShape()
{
}

double CircleShape::radius()
{
	return m_radius;
}

void CircleShape::GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max)
{
	i_min.x() = -m_radius;
	i_min.y() = -m_radius;
	i_max.x() = m_radius;
	i_max.y() = m_radius;
}

double CircleShape::GetArea()
{
	return PI * m_radius * m_radius;
}

