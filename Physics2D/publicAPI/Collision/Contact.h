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
	PhysicsVector normal = PhysicsVector();
	double penetration = 0.0;
	PhysicsVector* point1 = nullptr;
	PhysicsVector* point2 = nullptr;

private:

	void resolvePenetration() const;

	void resolveVelocity() const;

};
#endif 

