#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "Contact.h"
class CollisionDetector
{
public:

	CollisionDetector();

	~CollisionDetector();

	static bool CollisionDetect(PhysicsBody* i_bodyA, PhysicsBody* i_bodyB, Contact& i_contact);

private:


};
#endif 

