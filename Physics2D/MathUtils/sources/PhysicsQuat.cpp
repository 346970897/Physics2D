#include "PhysicsQuat.h"
#include "GlobalParameter.h"
#include <iostream>

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

PhysicsQuat PhysicsQuat::Normalize()
{
	double len = Magnitude();
	if(len < Epsilon)
		return *this;

	return PhysicsQuat(m_x / len, m_y / len, m_z / len, m_w / len);
}

PhysicsQuat PhysicsQuat::Conjugate() const
{
	return PhysicsQuat(-m_x, -m_y, -m_z, m_w);
}

PhysicsVector PhysicsQuat::MakeRotation(const PhysicsVector v) const
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

void PhysicsQuat::GetRotate(PhysicsVector& axis, double& angle) const
{
	angle = 2 * std::asin(m_w);
	double value = std::cos(angle);
	PhysicsVector v = PhysicsVector(m_x / value, m_y / value, m_z / value);
	axis = v.Normalize();
}

PhysicsVector PhysicsQuat::MakeEulerAngles() const
{
	PhysicsVector v = PhysicsVector();
	double matrix[3][3];
	ToRotationMatrix(matrix);
	double tmp = std::abs(matrix[2][0]);
	if (tmp > 0.999999)
	{
		v.x() = 0.0;
		v.y() = -HalfPI * matrix[2][0] / tmp;
		v.z() = std::atan2(-matrix[0][1], -matrix[2][0] * matrix[0][2]);
	}

	v.x() = std::atan2(matrix[2][1], matrix[1][2]);
	v.y() = std::asin(-matrix[2][0]);
	v.z() = std::atan2(matrix[1][0], matrix[0][0]);

	return v;
}

void PhysicsQuat::ToRotationMatrix(double matrix[3][3]) const
{
	double dblx = m_x * m_x;
	double dbly = m_y * m_y;
	double dblz = m_z * m_z;
	double dblw = m_w * m_w;

	matrix[0][0] = dblw + dblx - dbly - dblz;
	matrix[0][1] = 2 *(m_x * m_y - m_z * m_w);
	matrix[0][2] = 2 * (m_x * m_z + m_y * m_w);
	matrix[1][0] = 2 * (m_x * m_y + m_z * m_w);
	matrix[1][1] = dblw - dblx + dbly - dblw;;
	matrix[1][2] = 2 * (m_y * m_z + m_x * m_w);
	matrix[2][0] = 2 * (m_x * m_z - m_y * m_w);
	matrix[2][1] = 2 * (m_y * m_z + m_x * m_w);
	matrix[2][2] = dblw - dblx - dbly - dblw;
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

PhysicsQuat PhysicsQuat::operator+(const PhysicsQuat q) const
{
	return PhysicsQuat(m_x + q.m_x, m_y + q.m_y, m_z + q.m_z, m_w + q.m_w);
}

PhysicsQuat& PhysicsQuat::operator+=(const PhysicsQuat q)
{
	m_x += q.m_x;
	m_y += q.m_y;
	m_z += q.m_z;
	m_w += q.m_w;

	return *this;
}

PhysicsQuat PhysicsQuat::operator/(const double value) const
{
	return PhysicsQuat(m_x / value, m_y / value, m_z / value, m_w / value);
}

PhysicsQuat& PhysicsQuat::operator/=(const double value)
{
	m_x /= value;
	m_y /= value;
	m_z /= value;
	m_w /= value;

	return *this;
}
