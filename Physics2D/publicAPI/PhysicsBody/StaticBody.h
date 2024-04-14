#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include "PhysicsBody.h"

class StaticBody : public PhysicsBody
{
public:

	StaticBody(const PhysicsTransform globalPose);

	~StaticBody();

protected:

	void Simulation(const double time, const PhysicsVector gravity, const int iterator = 1) override;
};
#endif 

