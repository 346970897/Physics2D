#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
{
}

PhysicsBody::~PhysicsBody()
{
    if (m_shape)
        delete m_shape;
    m_shape = nullptr;
}

void PhysicsBody::GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max)
{
    PhysicsVector2D maxValue;
    PhysicsVector2D minValue;
    m_shape->GetAABB(minValue, maxValue);
    i_min = minValue + m_globaPose;
    i_max = maxValue + m_globaPose;
}

PhysicsVector2D PhysicsBody::GetGlobaPose()
{
    return m_globaPose;
}

void PhysicsBody::SetGlobaPose(const PhysicsVector2D i_globalPose)
{
    m_globaPose = i_globalPose;
}

void PhysicsBody::AddShape(PhysicsShape* i_shape)
{
    m_shape = i_shape;
}

PhysicsShape* PhysicsBody::GetShape()
{
    return m_shape;
}

BodyType PhysicsBody::GetBodyType() const
{
    return m_bodyType;
}

PhysicsVector2D PhysicsBody::GetLinearVelocity() const
{
    return m_linearVelocity;
}

void PhysicsBody::SetLinearVelocity(const PhysicsVector2D i_linearVel)
{
    m_linearVelocity = i_linearVel;
}

void PhysicsBody::AddLinearVelocity(const PhysicsVector2D i_linearVel)
{
    m_linearVelocity = m_linearVelocity + i_linearVel;
}

PhysicsVector2D PhysicsBody::GetAngularVelocity() const
{
    return m_angularVelocity;
}

void PhysicsBody::SetAngularVelocity(const PhysicsVector2D i_angularVel)
{
    m_angularVelocity = i_angularVel;
}

PhysicsVector2D PhysicsBody::GetForce() const
{
    return m_force;
}

void PhysicsBody::AddForce(const PhysicsVector2D i_force)
{
    m_force = i_force;
}

PhysicsVector2D PhysicsBody::GetTorque() const
{
    return m_torque;
}

void PhysicsBody::AddTorque(const PhysicsVector2D i_torque)
{
    m_torque = i_torque;
}

double PhysicsBody::GetInvMass() const
{
    return m_invMass;
}
