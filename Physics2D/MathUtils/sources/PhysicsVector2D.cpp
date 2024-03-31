#include "PhysicsVector2D.h"
#include "iostream"

#define TOLERANCE 1e-6

PhysicsVector2D::PhysicsVector2D()
{
	m_x = 0.0;
	m_y = 0.0;
}

PhysicsVector2D::PhysicsVector2D(const double x, const double y)
{
	m_x = x;
	m_y = y;
}

PhysicsVector2D::~PhysicsVector2D()
{

}

double& PhysicsVector2D::x()
{
	return m_x;
}

double& PhysicsVector2D::y()
{
	return m_y;
}

double PhysicsVector2D::DotProduct(const PhysicsVector2D v) const
{
	return m_x * v.m_x + m_y * v.m_y;
}

double PhysicsVector2D::GetLength()
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}

double PhysicsVector2D::GetLengthSquared()
{
	return m_x * m_x + m_y * m_y;
}

PhysicsVector2D PhysicsVector2D::Normalize() const
{
	PhysicsVector2D v = PhysicsVector2D();
	double len = std::sqrt(m_x * m_x + m_y * m_y);
	if (len >= TOLERANCE)
	{
		v.x() = m_x / len;
		v.y() = m_y / len;
	}
		
	return v;
}

PhysicsVector2D PhysicsVector2D::operator+(const PhysicsVector2D v) const
{
	return PhysicsVector2D(m_x + v.m_x, m_y + v.m_y);
}

PhysicsVector2D PhysicsVector2D::operator-(const PhysicsVector2D v) const
{
	return PhysicsVector2D(m_x - v.m_x, m_y - v.m_y);
}

PhysicsVector2D PhysicsVector2D::operator-() const
{
	return PhysicsVector2D(-m_x, -m_y);
}

PhysicsVector2D PhysicsVector2D::operator*(const double value) const
{
	return PhysicsVector2D(m_x * value, m_y * value);
}

void PhysicsVector2D::operator=(const PhysicsVector2D value)
{
	m_x = value.m_x;
	m_y = value.m_y;
}
