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

void PhysicsBody::GetAABB(PhysicsVector& min, PhysicsVector& max)
{
    min = PhysicsVector(DBL_MAX);
    max = PhysicsVector(-DBL_MAX);
    PhysicsVector maxValue;
    PhysicsVector minValue;
    m_shape->GetAABB(minValue, maxValue);
    for (int i = 0; i < 4; i++)
    {
        PhysicsVector point(0, 0, 0);
        point.x() = i > 1 ? maxValue.x() : minValue.x();
        point.y() = i % 2 == 0 ? maxValue.y() : minValue.y();
        point = m_globaPose * point;

        min.x() = std::min(point.x(), min.x());
        min.y() = std::min(point.y(), min.y());
        max.x() = std::max(point.x(), max.x());
        max.y() = std::max(point.y(), max.y());
    }
}

PhysicsTransform PhysicsBody::GetGlobaPose()
{
    return m_globaPose;
}

void PhysicsBody::SetGlobaPose(const PhysicsTransform globalPose)
{
    m_globaPose = globalPose;
}

void PhysicsBody::AddShape(PhysicsShape* shape)
{
    m_shape = shape;
}

PhysicsShape* PhysicsBody::GetShape()
{
    return m_shape;
}

BodyType PhysicsBody::GetBodyType() const
{
    return m_bodyType;
}

PhysicsVector PhysicsBody::GetLinearVelocity() const
{
    return m_linearVelocity;
}

void PhysicsBody::SetLinearVelocity(const PhysicsVector linearVel)
{
    m_linearVelocity = linearVel;
}

void PhysicsBody::AddLinearVelocity(const PhysicsVector linearVel)
{
    m_linearVelocity += linearVel;
}

PhysicsVector PhysicsBody::GetAngularVelocity() const
{
    return m_angularVelocity;
}

void PhysicsBody::SetAngularVelocity(const PhysicsVector angularVel)
{
    m_angularVelocity += angularVel;
}

void PhysicsBody::AddAngularVelocity(const PhysicsVector angularVel)
{
    m_angularVelocity = angularVel;
}

PhysicsVector PhysicsBody::GetForce() const
{
    return m_force;
}

void PhysicsBody::AddForce(const PhysicsVector force)
{
    m_force = force;
}

PhysicsVector PhysicsBody::GetTorque() const
{
    return m_torque;
}

void PhysicsBody::AddTorque(const PhysicsVector torque)
{
    m_torque = torque;
}

double PhysicsBody::GetInvMass() const
{
    return m_invMass;
}

double PhysicsBody::GetInvInertia() const
{
    return m_invInertia;
}
