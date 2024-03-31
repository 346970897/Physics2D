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

	virtual void GetAABB(PhysicsVector2D& i_min, PhysicsVector2D& i_max);

	PhysicsVector2D GetGlobaPose();

	void SetGlobaPose(const PhysicsVector2D i_globalPose);

	void AddShape(PhysicsShape* i_shape);

	PhysicsShape* GetShape();

	BodyType GetBodyType() const;

	PhysicsVector2D GetLinearVelocity() const;

	void SetLinearVelocity(const PhysicsVector2D i_linearVel);

	void AddLinearVelocity(const PhysicsVector2D i_linearVel);

	PhysicsVector2D GetAngularVelocity() const;

	void SetAngularVelocity(const PhysicsVector2D i_angularVel);

	PhysicsVector2D GetForce() const;

	void AddForce(const PhysicsVector2D i_force);

	PhysicsVector2D GetTorque() const;

	void AddTorque(const PhysicsVector2D i_torque);

	double GetInvMass() const;

	virtual void Simulation(const double i_time, const PhysicsVector2D i_gravity, const int iterator = 1) = 0;

protected:

	BodyType m_bodyType = BodyType::UNDEFINE_BODY;
	PhysicsVector2D m_globaPose = PhysicsVector2D();
	PhysicsShape* m_shape = nullptr;
	double m_mass = 0.0;
	double m_invMass = 0.0;
	PhysicsVector2D m_linearVelocity = PhysicsVector2D();
	PhysicsVector2D m_angularVelocity = PhysicsVector2D();
	PhysicsVector2D m_force = PhysicsVector2D();
	PhysicsVector2D m_torque = PhysicsVector2D();
};
#endif 

