#include "PhyscisShape.h"

PhysicsShape::PhysicsShape(const double restitution, const double staticFriction, const double dynamicFriction)
{
    m_restitution = restitution;
    m_staticFriction = staticFriction;
    m_dynamicFriction = dynamicFriction;
}

PhysicsShape::~PhysicsShape()
{
}

ShapeType PhysicsShape::GetShapeType() const
{
    return m_shapeType;
}

double PhysicsShape::GetRestitution() const
{
    return m_restitution;
}

double PhysicsShape::GetStaticFriction() const
{
    return m_staticFriction;
}

double PhysicsShape::GetDynamicFriction() const
{
    return m_dynamicFriction;
}
