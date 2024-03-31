#ifndef DYNAMIC_BODY_H
#define DYNAMIC_BODY_H

#include "PhysicsBody.h"

class DynamicBody : public PhysicsBody
{
public:

	DynamicBody(const PhysicsVector2D i_globalPose, const double i_density);

	~DynamicBody();

	double GetMass() const;

	void SetMass(const double i_mass);

	void UpdateMass();

	void MoveTo(const PhysicsVector2D i_pose);

protected:

	void Simulation(const double i_time, const PhysicsVector2D i_gravity, const int iterator = 1) override;

private:

	 double m_density = 1.0;
};
#endif 

