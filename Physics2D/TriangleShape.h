#pragma once
#ifndef TRIANGLE_SHAPE_H
#define TRIANGLE_SHAPE_H

#include"PhyscisShape.h"

class Triangle :public PhysicsShape
{
public:

	Triangle(const PhysicsVector& i_vertex1, const PhysicsVector& i_vertex2, const PhysicsVector& i_vertex3);

	~Triangle();

	void GetAABB(PhysicsVector& i_min, PhysicsVector& i_max) override;

	double GetArea() override;
};

#endif // !TRIANGLE_SHAPE_H