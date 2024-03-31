#ifndef COLLISION_CONTACT_H
#define COLLISION_CONTACT_H

#include "PhysicsBody.h"

class Contact
{
public:

	Contact();

	~Contact();

	void resolve();

public:

	PhysicsBody* bodyA = nullptr;
	PhysicsBody* bodyB = nullptr;
	PhysicsShape* shapeA = nullptr;
	PhysicsShape* shapeB = nullptr;
	PhysicsVector2D normal = PhysicsVector2D();
	double penetration = 0.0;

private:

	void resolvePenetraion() const;

	void resolveVelocity() const;

};
#endif 

