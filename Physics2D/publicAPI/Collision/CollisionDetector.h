#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "Contact.h"
class CollisionDetector
{
public:

	static bool CollisionDetect(PhysicsBody* bodyA, PhysicsBody* bodyB, Contact& contact);

private:

	CollisionDetector();

	~CollisionDetector();

	static bool IntersectAABB(PhysicsVector minA, PhysicsVector maxA, PhysicsVector minB, PhysicsVector maxB);

	static bool IntersectCircle(const PhysicsVector centerA, const double radiusA, const PhysicsVector centerB, const double radiusB, Contact& contact);

	static bool IntersectRectangle(std::vector<PhysicsVector> verticesA, const PhysicsTransform poseA, std::vector<PhysicsVector> verticesB, const PhysicsTransform poseB, Contact& contact);

	static bool IntersectRectangleAndCircle(std::vector<PhysicsVector> vertices, const PhysicsTransform pose, const PhysicsVector center, const double radius, Contact& contact);

	static void ProjectPolygon(const PhysicsVector axis, std::vector<PhysicsVector> vertices, const PhysicsTransform pose, double& min, double& max);

	static void ProjectCircle(const PhysicsVector axis, const double radius, const PhysicsVector center, double& min, double& max);
};
#endif 

