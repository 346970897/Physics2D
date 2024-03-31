#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "PhyscisShape.h"

class CircleShape : public PhysicsShape
{
public:

	CircleShape(const double i_radius);

	~CircleShape();

	double radius();

	void GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max) override;

	double GetArea() override;

private:

	double m_radius = 0.0;
};
#endif 

