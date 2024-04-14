#ifndef PHYSICS_TRANSFORM
#define PHYSICS_TRANSFORM

#include "PhysicsVector.h"
#include "PhysicsQuat.h"

class PhysicsTransform
{
public:

	PhysicsTransform();

	PhysicsTransform(const PhysicsVector position);

	PhysicsTransform(const PhysicsVector position, const PhysicsQuat rotation);

	~PhysicsTransform();

	PhysicsVector GetPosition() const;

	PhysicsQuat GetRotation() const;

	PhysicsVector operator* (const PhysicsVector v) const;

	PhysicsTransform operator* (const PhysicsTransform pose) const;

private:

	PhysicsVector m_position;
	PhysicsQuat m_rotation;
};
#endif