#include "PhysicsWorld.h"
#include "CollisionDetector.h"

PhysicsWorld* PhysicsWorld::CreatePhysicsWorld(const PhysicsVector2D i_gravity)
{
	return new PhysicsWorld(i_gravity);
}

PhysicsWorld::~PhysicsWorld()
{
	for (auto body : m_bodies)
		delete body;

	m_bodies.clear();
}

PhysicsWorld::PhysicsWorld(const PhysicsVector2D i_gravity)
{
	m_gravity = i_gravity;
}

std::vector<PhysicsBody*> PhysicsWorld::GetBodies() const
{
	return m_bodies;
}

void PhysicsWorld::AddBody(PhysicsBody* i_body)
{
	m_bodies.push_back(i_body);
}

PhysicsBody* PhysicsWorld::GetBodyByIndex(const int i_index)
{
	if (m_bodies.size() <= i_index)
		return nullptr;

	return m_bodies[i_index];
}

void PhysicsWorld::RemoveBodyByIndex(const int i_index)
{
	if (m_bodies.size() > i_index)
	{
		int index = 0;
		for (auto iterator = m_bodies.begin(); iterator != m_bodies.end(); iterator++)
		{
			if (index == i_index) 
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

void PhysicsWorld::Simulation(const double i_time, const int i_iter)
{
	for (int i = 0; i < i_iter; i++)
	{
		// update pose and velocity of body 
		for (auto body : m_bodies)
			body->Simulation(i_time, m_gravity, i_iter);

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
