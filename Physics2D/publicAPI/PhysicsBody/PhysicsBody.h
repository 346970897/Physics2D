#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "PhyscisShape.h"
#include "CircleShape.h"
#include "RectangleShape.h"

enum BodyType
{
	UNDEFINE_BODY = 1 << 0,
	DYNAMIC_BODY = 1 << 1,
	STATIC_BODY = 1 << 2,
};

class PhysicsBody
{
public:

	PhysicsBody();

	~PhysicsBody();

	virtual void GetAABB(PhysicsVector& min, PhysicsVector& max);

	PhysicsTransform GetGlobaPose();

	void SetGlobaPose(const PhysicsTransform globalPose);

	void AddShape(PhysicsShape* shape);

	PhysicsShape* GetShape();

	BodyType GetBodyType() const;

	PhysicsVector GetLinearVelocity() const;

	void SetLinearVelocity(const PhysicsVector linearVel);

	void AddLinearVelocity(const PhysicsVector linearVel);

	PhysicsVector GetAngularVelocity() const;

	void SetAngularVelocity(const PhysicsVector angularVel);

	PhysicsVector GetForce() const;

	void AddForce(const PhysicsVector force);

	PhysicsVector GetTorque() const;

	void AddTorque(const PhysicsVector torque);

	double GetInvMass() const;

	double GetInvInertia() const;

	virtual void Simulation(const double time, const PhysicsVector gravity, const int iterator = 1) = 0;

protected:

	BodyType m_bodyType = BodyType::UNDEFINE_BODY;
	PhysicsTransform m_globaPose = PhysicsTransform();
	PhysicsShape* m_shape = nullptr;
	double m_mass = 0.0;
	double m_invMass = 0.0;
	double m_inertia = 0.0;
	double m_invInertia = 0.0;
	PhysicsVector m_linearVelocity = PhysicsVector();
	PhysicsVector m_angularVelocity = PhysicsVector();
	PhysicsVector m_force = PhysicsVector();
	PhysicsVector m_torque = PhysicsVector();
};
#endif 

