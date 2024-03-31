#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include "PhysicsBody.h"
#include "StaticBody.h"
#include "DynamicBody.h"

class PhysicsWorld
{
public: 

	static PhysicsWorld* CreatePhysicsWorld(const PhysicsVector2D i_gravity = PhysicsVector2D(0, -9.8));

	std::vector<PhysicsBody*> GetBodies() const;

	void AddBody(PhysicsBody* i_body);

	PhysicsBody* GetBodyByIndex(const int i_index);

	void RemoveBodyByIndex(const int i_index);

	void ResetBodies();

	void Simulation(const double i_time, const int i_iter = 1);

private:

	PhysicsWorld(const PhysicsVector2D i_gravity);

	~PhysicsWorld();

private:

	std::vector<PhysicsBody*> m_bodies;
	PhysicsVector2D m_gravity = PhysicsVector2D();

};
#endif
