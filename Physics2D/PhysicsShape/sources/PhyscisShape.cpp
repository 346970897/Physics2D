#include "PhyscisShape.h"

PhysicsShape::PhysicsShape(const double i_restitution, const double i_staticFriction, const double i_dynamicFriction)
{
    m_restitution = i_restitution;
    m_staticFriction = i_staticFriction;
    m_dynamicFriction = i_dynamicFriction;
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
