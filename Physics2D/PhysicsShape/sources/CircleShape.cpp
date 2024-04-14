#include "CircleShape.h"

CircleShape::CircleShape(const double radius): PhysicsShape()
{
	m_shapeType = ShapeType::CIRCLE_SHAPE;
	m_radius = radius;
}

CircleShape::~CircleShape()
{
}

double CircleShape::radius()
{
	return m_radius;
}

void CircleShape::GetAABB(PhysicsVector& min, PhysicsVector& max)
{
	min.x() = -m_radius;
	min.y() = -m_radius;
	max.x() = m_radius;
	max.y() = m_radius;
}

double CircleShape::GetArea()
{
	return PI * m_radius * m_radius;
}

