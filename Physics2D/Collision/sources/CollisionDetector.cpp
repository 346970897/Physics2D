#include "CollisionDetector.h"
#include "CircleShape.h"
#include "RectangleShape.h"

CollisionDetector::CollisionDetector()
{

}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::CollisionDetect(PhysicsBody* bodyA, PhysicsBody* bodyB, Contact& contact)
{
	bool isCollide = false;
	if (!bodyA || !bodyB)
		return false;

	PhysicsShape* shapeA = bodyA->GetShape();
	PhysicsShape* shapeB = bodyB->GetShape();
	if (!shapeA || !shapeB)
		return false;

	PhysicsVector minA, maxA, minB, maxB;
	bodyA->GetAABB(minA, maxA);
	bodyB->GetAABB(minB, maxB);
	if(!IntersectAABB(minA, maxA, minB, maxB))
		return false;

	contact.bodyA = bodyA;
	contact.bodyB = bodyB;
	contact.shapeA = shapeA;
	contact.shapeB = shapeB;

	if (shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE && shapeB->GetShapeType() & ShapeType::CIRCLE_SHAPE)
	{
		CircleShape* circleShpaeA = dynamic_cast<CircleShape*>(shapeA);
		CircleShape* circleShpaeB = dynamic_cast<CircleShape*>(shapeB);
		if (!circleShpaeA || !circleShpaeB)
			return isCollide;

		isCollide = IntersectCircle(bodyA->GetGlobaPose().GetPosition(), circleShpaeA->radius(), bodyB->GetGlobaPose().GetPosition(), circleShpaeB->radius(), contact);		
		contact.collideType = CollideType::CircleVsCircle;
	}			
	else if (shapeA->GetShapeType() & ShapeType::RECTANGLE_SHAPE && shapeB->GetShapeType() & ShapeType::RECTANGLE_SHAPE)
	{
		RectangleShape* rectangleShpaeA = dynamic_cast<RectangleShape*>(shapeA);
		RectangleShape* rectangleShpaeB = dynamic_cast<RectangleShape*>(shapeB);
		if (!rectangleShpaeA || !rectangleShpaeB)
			return isCollide;

		isCollide = IntersectRectangle(rectangleShpaeA->GetVertices(), bodyA->GetGlobaPose(), rectangleShpaeB->GetVertices(), bodyB->GetGlobaPose(), contact);
		contact.collideType = CollideType::RectangleVsRectangle;
	}
	else if (shapeA->GetShapeType() & ShapeType::RECTANGLE_SHAPE && shapeB->GetShapeType() & ShapeType::CIRCLE_SHAPE ||
		shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE && shapeB->GetShapeType() & ShapeType::RECTANGLE_SHAPE)
	{
		CircleShape* circleShpae = nullptr;
		RectangleShape* rectangleShape = nullptr;
		PhysicsVector center;
		PhysicsTransform pose;
		if (shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE)
		{
			circleShpae = dynamic_cast<CircleShape*>(shapeA);
			center = bodyA->GetGlobaPose().GetPosition();
			rectangleShape = dynamic_cast<RectangleShape*>(shapeB);
			pose = bodyB->GetGlobaPose();

			contact.bodyA = bodyB;
			contact.bodyB = bodyA;
			contact.shapeA = shapeB;
			contact.shapeB = shapeA;
		}
		else
		{
			circleShpae = dynamic_cast<CircleShape*>(shapeB);
			center = bodyB->GetGlobaPose().GetPosition();
			rectangleShape = dynamic_cast<RectangleShape*>(shapeA);
			pose = bodyA->GetGlobaPose();
		}
		isCollide = IntersectRectangleAndCircle(rectangleShape->GetVertices(), pose, center, circleShpae->radius(), contact);
		contact.collideType = CollideType::RectangleVsCircle;
	}
	
	return isCollide;
}

bool CollisionDetector::IntersectAABB(PhysicsVector minA, PhysicsVector maxA, PhysicsVector minB, PhysicsVector maxB)
{
	bool isCollide = true;

	if (minA.x() > maxB.x() || maxA.x() < minB.x() || minA.y() > maxB.y() || maxA.y() < minB.y())
		return false;

	return isCollide;
}

bool CollisionDetector::IntersectCircle(const PhysicsVector centerA, const double radiusA, const PhysicsVector centerB, const double radiusB, Contact& contact)
{
	bool isIntersect = false;

	PhysicsVector normal = centerA - centerB;
	double distance = normal.GetLength();
	isIntersect = distance <= radiusA + radiusB;

	if (isIntersect)
	{
		contact.penetration = radiusA + radiusB - distance;
		contact.normal = normal.Normalize();
	}

	return isIntersect;
}

bool CollisionDetector::IntersectRectangle(std::vector<PhysicsVector> verticesA, const PhysicsTransform poseA, std::vector<PhysicsVector> verticesB, const PhysicsTransform poseB, Contact& contact)
{
	bool isIntersect = true;

	std::vector<PhysicsVector> axisList;
	// get axis for project
	for (int i = 0; i < 2; i++)
	{
		PhysicsVector point1 = poseA * verticesA[i];
		PhysicsVector point2 = poseA * verticesA[i + 1];
		PhysicsVector vectorA = point2 - point1;
		point1 = poseB * verticesB[i];
		point2 = poseB * verticesB[i + 1];
		PhysicsVector vectorB = point2 - point1;
		vectorA = vectorA.Normalize();
		vectorB = vectorB.Normalize();
		vectorA = PhysicsVector(-vectorA.y(), vectorA.x(), 0);
		vectorB = PhysicsVector(vectorB.y(), -vectorB.x(), 0);

		axisList.push_back(vectorA);
		axisList.push_back(vectorB);
	}

	// loop axis, compute penetraion and normal
	double penetraion = DBL_MAX;
	PhysicsVector normal;
	for (auto axis : axisList)
	{
		double minValueA, maxValueA, minValueB, maxValueB;
		ProjectPolygon(axis, verticesA, poseA, minValueA, maxValueA);
		ProjectPolygon(axis, verticesB, poseB, minValueB, maxValueB);
		double depth = std::min(maxValueA, maxValueB) - std::max(minValueA, minValueB);
		if (depth < 0)
			return false;

		if (penetraion > depth)
		{
			penetraion = depth;
			normal = axis;
		}
	}
	PhysicsVector v = poseA.GetPosition() - poseB.GetPosition();
	if (v.DotProduct(normal) < 0)
		normal = -normal;

	contact.penetration = penetraion;
	contact.normal = normal;

	return isIntersect;
}

bool CollisionDetector::IntersectRectangleAndCircle(std::vector<PhysicsVector> vertices, const PhysicsTransform pose, const PhysicsVector center, const double radius, Contact& contact)
{
	bool isIntersect = true;

	std::vector<PhysicsVector> axisList;
	// get axis for project
	for (int i = 0; i < 2; i++)
	{
		PhysicsVector vectorA = vertices[i + 1] - vertices[i];
		vectorA = vectorA.Normalize();
		vectorA = PhysicsVector(-vectorA.y(), vectorA.x(), 0);

		axisList.push_back(vectorA);
	}
	// find closest point on circle
	PhysicsVector closestPoint;
	double distance = DBL_MAX;
	for (auto vertice : vertices)
	{
		PhysicsVector point = pose * vertice;
		double len = (point  - center).GetLength();
		if (distance > len)
		{
			closestPoint = point;
			distance = len;
		}
	}
	axisList.push_back((closestPoint - center).Normalize());

	// loop axis, compute penetraion and normal
	double penetraion = DBL_MAX;
	PhysicsVector normal;
	for (auto axis : axisList)
	{
		double minValueA, maxValueA, minValueB, maxValueB;
		ProjectPolygon(axis, vertices, pose, minValueA, maxValueA);
		ProjectCircle(axis, radius, center, minValueB, maxValueB);
		double depth = std::min(maxValueB - minValueA, maxValueA - minValueB);
		if (depth < 0)
			return false;

		if (penetraion > depth)
		{
			penetraion = depth;
			normal = axis;
		}
	}

	PhysicsVector v = pose.GetPosition() - center;
	if(v.DotProduct(normal) < 0)
		normal = -normal;

	contact.penetration = penetraion;
	contact.normal = normal;

	return isIntersect;
}

void CollisionDetector::ProjectPolygon(const PhysicsVector axis, std::vector<PhysicsVector> vertices, const PhysicsTransform pose, double& min, double& max)
{
	double minValue = DBL_MAX;
	double maxValue = -DBL_MAX;
	for (auto vertice : vertices)
	{
		PhysicsVector vec = pose * vertice;
		double value = vec.DotProduct(axis);
		minValue = value < minValue ? value : minValue;
		maxValue = value > maxValue ? value : maxValue;
	}

	min = minValue;
	max = maxValue;
}

void CollisionDetector::ProjectCircle(const PhysicsVector axis, const double radius, const PhysicsVector center, double& min, double& max)
{
	double dotValue = center.DotProduct(axis);
	min = dotValue - radius;
	max = dotValue + radius;
}