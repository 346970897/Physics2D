#include "PhysicsVector.h"
#include "iostream"

#define TOLERANCE 1e-6

PhysicsVector::PhysicsVector()
{
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
}

PhysicsVector::PhysicsVector(const double value)
{
	m_x = value;
	m_y = value;
	m_z = value;
}

PhysicsVector::PhysicsVector(const double x, const double y, const double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

PhysicsVector::~PhysicsVector()
{

}

double& PhysicsVector::x()
{
	return m_x;
}

double& PhysicsVector::y()
{
	return m_y;
}

double& PhysicsVector::z()
{
	return m_z;
}

double PhysicsVector::DotProduct(const PhysicsVector v) const
{
	return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

PhysicsVector PhysicsVector::CrossProduct(const PhysicsVector v) const
{
	return PhysicsVector(m_y * v.m_z - m_z * v.m_y, m_x * v.m_z - m_z * v.m_x, m_x * v.m_y - m_y * v.m_x);
}

double PhysicsVector::GetLength()
{
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

double PhysicsVector::GetLengthSquared()
{
	return m_x * m_x + m_y * m_y + m_z * m_z;
}

PhysicsVector PhysicsVector::Normalize() 
{
	PhysicsVector v = PhysicsVector();
	double len = GetLength();
	if (len >= TOLERANCE)
	{
		v.x() = m_x / len;
		v.y() = m_y / len;
		v.z() = m_z / len;
	}
		
	return v;
}

PhysicsVector PhysicsVector::operator+(const PhysicsVector v) const
{
	return PhysicsVector(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}

PhysicsVector& PhysicsVector::operator+=(const PhysicsVector v)
{
	m_x = m_x + v.m_x;
	m_y = m_y + v.m_y;
	m_z = m_z + v.m_z;

	return *this;
}

PhysicsVector PhysicsVector::operator-(const PhysicsVector v) const
{
	return PhysicsVector(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
}

PhysicsVector& PhysicsVector::operator-=(const PhysicsVector v)
{
	m_x = m_x - v.m_x;
	m_y = m_y - v.m_y;
	m_z = m_z - v.m_z;

	return *this;
}

PhysicsVector PhysicsVector::operator-() const
{
	return PhysicsVector(-m_x, -m_y, -m_z);
}

PhysicsVector PhysicsVector::operator*(const double value) const
{
	return PhysicsVector(m_x * value, m_y * value, m_z * value);
}

PhysicsVector& PhysicsVector::operator*=(const double value)
{
	m_x = m_x * value;
	m_y = m_y * value;
	m_z = m_z * value;

	return *this;
}

PhysicsVector PhysicsVector::operator/(const double value) const
{
	if (value < 1e-12)
		return PhysicsVector();

	return PhysicsVector(m_x / value, m_y / value, m_z / value);
}

PhysicsVector& PhysicsVector::operator/=(const double value)
{
	if (value < 1e-12)
		return *this;

	m_x = m_x / value;
	m_y = m_y / value;
	m_z = m_z / value;

	return *this;
}

void PhysicsVector::operator=(const PhysicsVector value)
{
	m_x = value.m_x;
	m_y = value.m_y;
	m_z = value.m_z;
}
