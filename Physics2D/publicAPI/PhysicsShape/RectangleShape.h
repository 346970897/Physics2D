#ifndef RECTANGLE_SHAPE_H
#define RECTANGLE_SHAPE_H

#include "PhyscisShape.h"

class RectangleShape : public PhysicsShape
{
public:

	RectangleShape(const double i_halfWidth, const double i_halfHeight);

	~RectangleShape();

	std::vector<PhysicsVector2D> GetVertices() const;

	double width();

	double height();

	void GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max) override;

	double GetArea() override;

private:

	std::vector<PhysicsVector2D> m_vertices;
	double m_halfWidth = 0.0;
	double m_halfHeight = 0.0;
};
#endif 

