#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

#include "GlobalParameter.h"
#include "PhysicsTransform.h"

enum ShapeType
{
	UNDEFINE_SHAPE = 1 << 0,
	CIRCLE_SHAPE = 1 << 1,
	RECTANGLE_SHAPE = 1 << 2,
	CONVEX_SHAPE = 1 << 3
};

class PhysicsShape
{
public:

	PhysicsShape(const double restitution = 0.2, const double staticFriction = 0.1, const double dynamicFriction = 0.1);

	~PhysicsShape();

	ShapeType GetShapeType() const;

	double GetRestitution() const;

	double GetStaticFriction() const;

	double GetDynamicFriction() const;

	virtual void GetAABB(PhysicsVector& i_min, PhysicsVector& i_max) = 0;

	virtual double GetArea() = 0;

protected:

	ShapeType m_shapeType = ShapeType::UNDEFINE_SHAPE;
	double m_restitution = 0.8;
	double m_staticFriction = 0.1;
	double m_dynamicFriction = 0.1;
};
#endif 

