#include "PhysicsTransform.h"

PhysicsTransform::PhysicsTransform()
{
	m_position = PhysicsVector();
	m_rotation = PhysicsQuat();
}

PhysicsTransform::PhysicsTransform(const PhysicsVector position)
{
	m_position = position;
	m_rotation = PhysicsQuat();
}

PhysicsTransform::PhysicsTransform(const PhysicsVector position, const PhysicsQuat rotation)
{
	m_position = position;
	m_rotation = rotation;
}

PhysicsTransform::~PhysicsTransform()
{

}

PhysicsVector PhysicsTransform::GetPosition() const
{
	return m_position;
}

PhysicsQuat PhysicsTransform::GetRotation() const
{
	return m_rotation;
}

PhysicsVector PhysicsTransform::operator*(const PhysicsVector v) const
{
	 PhysicsVector retval = v;
	 retval = m_rotation.MakeRotation(retval);
	 retval += m_position;

	 return retval;
}

PhysicsTransform PhysicsTransform::operator*(const PhysicsTransform pose) const
{
	PhysicsTransform transform = PhysicsTransform();
	transform.m_position = pose.m_rotation.MakeRotation(m_position) + pose.m_position;
	transform.m_rotation = m_rotation * pose.m_rotation;

	return transform;
}
