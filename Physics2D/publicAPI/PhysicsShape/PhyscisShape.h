#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

#include "GlobalParameter.h"
#include "PhysicsVector2D.h"

enum ShapeType
{
	UNDEFINE_SHAPE = 1 << 0,
	CIRCLE_SHAPE = 1 << 1,
	RECTANGLE_SHAPE = 1 << 2,
	POLYGAN_SHAPE = 1 << 3
};

class PhysicsShape
{
public:

	PhysicsShape(const double m_restitution = 0.8, const double m_staticFriction = 0.1, const double m_dynamicFriction = 0.1);

	~PhysicsShape();

	ShapeType GetShapeType() const;

	double GetRestitution() const;

	double GetStaticFriction() const;

	double GetDynamicFriction() const;

	virtual void GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max) = 0;

	virtual double GetArea() = 0;

protected:

	ShapeType m_shapeType = ShapeType::UNDEFINE_SHAPE;
	double m_restitution = 0.8;
	double m_staticFriction = 0.1;
	double m_dynamicFriction = 0.1;
};
#endif 

