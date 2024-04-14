#include "PhysicsWorld.h"
#include "CollisionDetector.h"

PhysicsWorld* PhysicsWorld::CreatePhysicsWorld(const PhysicsVector gravity)
{
	return new PhysicsWorld(gravity);
}

PhysicsWorld::~PhysicsWorld()
{
	for (auto body : m_bodies)
		delete body;

	m_bodies.clear();
}

PhysicsWorld::PhysicsWorld(const PhysicsVector gravity)
{
	m_gravity = gravity;
}

std::vector<PhysicsBody*> PhysicsWorld::GetBodies() const
{
	return m_bodies;
}

void PhysicsWorld::AddBody(PhysicsBody* body)
{
	m_bodies.push_back(body);
}

PhysicsBody* PhysicsWorld::GetBodyByIndex(const int index)
{
	if (m_bodies.size() <= index)
		return nullptr;

	return m_bodies[index];
}

void PhysicsWorld::RemoveBodyByIndex(const int index)
{
	if (m_bodies.size() > index)
	{
		int index = 0;
		for (auto iterator = m_bodies.begin(); iterator != m_bodies.end(); iterator++)
		{
			if (index == index) 
			{
				m_bodies.erase(iterator);
				delete *iterator;
				return;
			}
			index++;
		}
	}
}

void PhysicsWorld::ResetBodies()
{
	for (auto body : m_bodies)
		delete body;

	m_bodies.clear();
}

void PhysicsWorld::Simulation(const double time, const int iter)
{
	for (int i = 0; i < iter; i++)
	{
		// update pose and velocity of body 
		for (auto body : m_bodies)
			body->Simulation(time, m_gravity, iter);

		// process collide
		for (int j = 0; j < m_bodies.size(); j++)
		{
			PhysicsBody* bodyA = m_bodies[j];
			for (int k = j + 1; k < m_bodies.size(); k++)
			{
				PhysicsBody* bodyB = m_bodies[k];
				if (bodyA->GetBodyType() & BodyType::STATIC_BODY && bodyB->GetBodyType() & BodyType::STATIC_BODY)
					continue;

				Contact contact;
				bool isCollide = CollisionDetector::CollisionDetect(bodyA, bodyB, contact);

				if (isCollide)
					contact.resolve();
			}
		}

	}
}
