#ifndef COLLISION_CONTACT_H
#define COLLISION_CONTACT_H

#include "PhysicsBody.h"

enum CollideType
{
	Undefined = 1 << 0,
	CircleVsCircle = 1 << 1,
	RectangleVsCircle = 1 << 2,
	RectangleVsRectangle = 1 << 3
};

//class ContactCallback
//{
//	virtual void onContact(const Contact contact) = 0;
//};

class Contact
{
public:

	Contact();

	~Contact();

	void Resolve();

public:

	PhysicsBody* bodyA = nullptr;
	PhysicsBody* bodyB = nullptr;
	PhysicsShape* shapeA = nullptr;
	PhysicsShape* shapeB = nullptr;
	PhysicsVector normal = PhysicsVector();
	double penetration = 0.0;
	std::vector<PhysicsVector> contactPoint;
	CollideType collideType = CollideType::Undefined;

private: 

	void ResolvePenetration() const;

	void ResolveVelocity() const;

	void ResolveContactPoint();

	void FindPointInCircles();

	void FindPointInPolygonAndCircle();

	void FindPointInPolygons();

};
#endif 

