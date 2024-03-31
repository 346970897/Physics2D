#include "StaticBody.h"

StaticBody::StaticBody(const PhysicsVector2D i_globalPose)
{
	m_bodyType = BodyType::STATIC_BODY;
	m_globaPose = i_globalPose;
	m_invMass = 0;
}

StaticBody::~StaticBody()
{
}

void StaticBody::Simulation(const double i_time, const PhysicsVector2D i_gravity, const int iterator)
{
}


