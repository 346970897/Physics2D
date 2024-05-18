#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include "PhysicsBody.h"
#include "StaticBody.h"
#include "DynamicBody.h"
#include "Contact.h"

class PhysicsWorld
{
public: 

	static PhysicsWorld* CreatePhysicsWorld(const PhysicsVector gravity = PhysicsVector(0, -9.8, 0));

	std::vector<PhysicsBody*> GetBodies() const;

	void AddBody(PhysicsBody* body);

	PhysicsBody* GetBodyByIndex(const int index);

	void RemoveBodyByIndex(const int index);

	void ResetBodies();

	void Simulation(const double time, const int iter = 1);

	void SetContactCallback();

private:

	PhysicsWorld(const PhysicsVector gravity);

	~PhysicsWorld();

private:

	std::vector<PhysicsBody*> m_bodies;
	PhysicsVector m_gravity = PhysicsVector();
	//ContactCallback* m_contact = nullptr;
};
#endif
