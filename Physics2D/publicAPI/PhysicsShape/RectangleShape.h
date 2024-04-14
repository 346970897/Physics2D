#ifndef RECTANGLE_SHAPE_H
#define RECTANGLE_SHAPE_H

#include "PhyscisShape.h"

class RectangleShape : public PhysicsShape
{
public:

	RectangleShape(const double halfWidth, const double halfHeight);

	~RectangleShape();

	std::vector<PhysicsVector> GetVertices() const;

	double width();

	double height();

	void GetAABB(PhysicsVector& min, PhysicsVector& max) override;

	double GetArea() override;

private:

	std::vector<PhysicsVector> m_vertices;
	double m_halfWidth = 0.0;
	double m_halfHeight = 0.0;
};
#endif 

