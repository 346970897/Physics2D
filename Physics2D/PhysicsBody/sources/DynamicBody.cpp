#include "DynamicBody.h"

DynamicBody::DynamicBody(const PhysicsVector2D i_globalPose, const double i_density)
{
	m_bodyType = BodyType::DYNAMIC_BODY;
	m_globaPose = i_globalPose;
	m_density = i_density;
}

DynamicBody::~DynamicBody()
{
}

double DynamicBody::GetMass() const
{
	return m_mass;
}

void DynamicBody::SetMass(const double i_mass)
{
	if (i_mass >= Epsilon)
	{
		m_mass = i_mass;
		m_invMass = 1 / m_mass;
	}
}

void DynamicBody::UpdateMass()
{
	if (!m_shape)
		return;
	double mass = m_density * m_shape->GetArea();
	if (mass >= Epsilon)
	{
		m_mass = mass;
		m_invMass = 1 / m_mass;
	}
}

void DynamicBody::MoveTo(const PhysicsVector2D i_pose)
{
	m_globaPose = m_globaPose + i_pose;
}

void DynamicBody::Simulation(const double i_time, const PhysicsVector2D i_gravity, const int iterator)
{
	double stepTime = i_time / iterator;
	PhysicsVector2D m_linearAccele = i_gravity + m_force * m_invMass;
	m_linearVelocity = m_linearVelocity + m_linearAccele * stepTime;
	m_globaPose = m_globaPose + m_linearVelocity * stepTime;
}

