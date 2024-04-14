#ifndef DYNAMIC_BODY_H
#define DYNAMIC_BODY_H

#include "PhysicsBody.h"

class DynamicBody : public PhysicsBody
{
public:

	DynamicBody(const PhysicsTransform globalPose, const double density);

	~DynamicBody();

	double GetMass() const;

	void SetMass(const double mass);

	void UpdateMass();

	void MoveTo(const PhysicsTransform pose);

protected:

	void Simulation(const double time, const PhysicsVector gravity, const int iterator = 1) override;

private:

	 double m_density = 1.0;
};
#endif 

