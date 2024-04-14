#include "PhysicsQuat.h"
#include "GlobalParameter.h"

PhysicsQuat::PhysicsQuat()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_w = 1;
}

PhysicsQuat::PhysicsQuat(const double x, const double y, const double z, const double w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

PhysicsQuat::PhysicsQuat(PhysicsVector v, const double w)
{
	m_x = v.x();
	m_y = v.y();
	m_z = v.z();
	m_w = w;
}

PhysicsQuat::~PhysicsQuat()
{
}


double PhysicsQuat::x() const
{
	return m_x;
}

double PhysicsQuat::y() const
{
	return m_y;
}

double PhysicsQuat::z() const
{
	return m_z;
}

double PhysicsQuat::w() const
{
	return m_w;
}

double PhysicsQuat::Magnitude()
{
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

PhysicsQuat PhysicsQuat::Conjugate() const
{
	return PhysicsQuat(-m_x, -m_y, -m_z, m_w);
}

PhysicsVector PhysicsQuat::operator*(const PhysicsVector v) const
{
	double len = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	if (len < Epsilon)
		return v;

	PhysicsQuat q(m_x / len, m_y / len, m_z / len, m_w / len);
	PhysicsQuat q1(v, 0);
	q1 = q * q1;
	q1 = q1 * q.Conjugate();
	
	return PhysicsVector(q1.m_x, q1.m_y, q1.m_z);
}

PhysicsQuat PhysicsQuat::operator*(const PhysicsQuat q) const
{
	return PhysicsQuat(m_w * q.m_x + m_x * q.m_w + m_y * q.m_z - m_z * q.m_y,
					   m_w * q.m_y - m_x * q.m_z + m_y * q.m_w + m_z * q.m_x,
					   m_w * q.m_z + m_x * q.m_y - m_y * q.m_x + m_z * q.m_w,
					   m_w * q.m_w - m_x * q.m_x - m_y * q.m_y - m_z * q.m_z);
}

PhysicsQuat& PhysicsQuat::operator*=(const PhysicsQuat q)
{
	double x = m_w * q.m_x + m_x * q.m_w + m_y * q.m_z - m_z * q.m_y;
	double y = m_w * q.m_y - m_x * q.m_z + m_y * q.m_w + m_z * q.m_x;
	double z = m_w * q.m_z + m_x * q.m_y - m_y * q.m_x + m_z * q.m_w;
	double w = m_w * q.m_w - m_x * q.m_x - m_y * q.m_y - m_z * q.m_z;

	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;

	return *this;
}
