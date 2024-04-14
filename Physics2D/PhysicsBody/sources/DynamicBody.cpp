#include "DynamicBody.h"

DynamicBody::DynamicBody(const PhysicsTransform globalPose, const double density)
{
	m_bodyType = BodyType::DYNAMIC_BODY;
	m_globaPose = globalPose;
	m_density = density;
}

DynamicBody::~DynamicBody()
{
}

double DynamicBody::GetMass() const
{
	return m_mass;
}

void DynamicBody::SetMass(const double mass)
{
	if (mass >= Epsilon)
	{
		m_mass = mass;
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

void DynamicBody::MoveTo(const PhysicsTransform pose)
{
	m_globaPose = m_globaPose * pose;
}

void DynamicBody::Simulation(const double time, const PhysicsVector gravity, const int iterator)
{
	double stepTime = time / iterator;
	PhysicsVector m_linearAccele = gravity + m_force * m_invMass;
	m_linearVelocity = m_linearVelocity + m_linearAccele * stepTime;
	m_globaPose = m_globaPose * PhysicsTransform((m_linearVelocity * stepTime));
}

