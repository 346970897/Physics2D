#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include "PhysicsBody.h"

class StaticBody : public PhysicsBody
{
public:

	StaticBody(const PhysicsVector2D i_globalPose);

	~StaticBody();

protected:

	void Simulation(const double i_time, const PhysicsVector2D i_gravity, const int iterator = 1) override;
};
#endif 

