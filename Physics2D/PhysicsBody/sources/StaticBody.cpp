#include "StaticBody.h"

StaticBody::StaticBody(const PhysicsTransform globalPose)
{
	m_bodyType = BodyType::STATIC_BODY;
	m_globaPose = globalPose;
	m_invMass = 0;
}

StaticBody::~StaticBody()
{
}

void StaticBody::Simulation(const double time, const PhysicsVector gravity, const int iterator)
{
}


