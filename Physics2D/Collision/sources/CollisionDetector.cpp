#include "CollisionDetector.h"
#include "CircleShape.h"
#include "RectangleShape.h"

bool IntersectCircle(const PhysicsVector2D i_centerA, const double i_radiusA, const PhysicsVector2D i_centerB, const double i_radiusB, Contact& i_contact);

bool IntersectRectangle(std::vector<PhysicsVector2D> i_verticesA, const PhysicsVector2D i_poseA, std::vector<PhysicsVector2D> i_verticesB, const PhysicsVector2D i_poseB, Contact& i_contact);

bool IntersectRectangleAndCircle(std::vector<PhysicsVector2D> i_vertices, const PhysicsVector2D i_pose, const PhysicsVector2D i_center, const double i_radius, Contact& i_contact);

void ProjectPolygon(const PhysicsVector2D i_axis, std::vector<PhysicsVector2D> i_vertices, const PhysicsVector2D i_pose, double& i_min, double& i_max);

void ProjectCircle(const PhysicsVector2D i_axis, const double i_radius, const PhysicsVector2D i_center, double& i_min, double& i_max);


CollisionDetector::CollisionDetector()
{

}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::CollisionDetect(PhysicsBody* i_bodyA, PhysicsBody* i_bodyB, Contact& i_contact)
{
	bool isCollide = false;
	if (!i_bodyA || !i_bodyB)
		return isCollide;

	PhysicsShape* shapeA = i_bodyA->GetShape();
	PhysicsShape* shapeB = i_bodyB->GetShape();
	if (!shapeA || !shapeB)
		return isCollide;

	i_contact.bodyA = i_bodyA;
	i_contact.bodyB = i_bodyB;
	i_contact.shapeA = shapeA;
	i_contact.shapeB = shapeB;

	if (shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE && shapeB->GetShapeType() & ShapeType::CIRCLE_SHAPE)
	{
		CircleShape* circleShpaeA = dynamic_cast<CircleShape*>(shapeA);
		CircleShape* circleShpaeB = dynamic_cast<CircleShape*>(shapeB);
		if (!circleShpaeA || !circleShpaeB)
			return isCollide;

		isCollide = IntersectCircle(i_bodyA->GetGlobaPose(), circleShpaeA->radius(), i_bodyB->GetGlobaPose(), circleShpaeB->radius(), i_contact);
	}			
	else if (shapeA->GetShapeType() & ShapeType::RECTANGLE_SHAPE && shapeB->GetShapeType() & ShapeType::RECTANGLE_SHAPE)
	{
		RectangleShape* rectangleShpaeA = dynamic_cast<RectangleShape*>(shapeA);
		RectangleShape* rectangleShpaeB = dynamic_cast<RectangleShape*>(shapeB);
		if (!rectangleShpaeA || !rectangleShpaeB)
			return isCollide;

		isCollide = IntersectRectangle(rectangleShpaeA->GetVertices(), i_bodyA->GetGlobaPose(), rectangleShpaeB->GetVertices(), i_bodyB->GetGlobaPose(), i_contact);
	}
	else if (shapeA->GetShapeType() & ShapeType::RECTANGLE_SHAPE && shapeB->GetShapeType() & ShapeType::CIRCLE_SHAPE ||
		shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE && shapeB->GetShapeType() & ShapeType::RECTANGLE_SHAPE)
	{
		CircleShape* circleShpae = nullptr;
		RectangleShape* rectangleShape = nullptr;
		PhysicsVector2D center, pose;
		if (shapeA->GetShapeType() & ShapeType::CIRCLE_SHAPE)
		{
			circleShpae = dynamic_cast<CircleShape*>(shapeA);
			center = i_bodyA->GetGlobaPose();
			rectangleShape = dynamic_cast<RectangleShape*>(shapeB);
			pose = i_bodyB->GetGlobaPose();

			i_contact.bodyA = i_bodyB;
			i_contact.bodyB = i_bodyA;
		}
		else
		{
			circleShpae = dynamic_cast<CircleShape*>(shapeB);
			center = i_bodyB->GetGlobaPose();
			rectangleShape = dynamic_cast<RectangleShape*>(shapeA);
			pose = i_bodyA->GetGlobaPose();
		}
		isCollide = IntersectRectangleAndCircle(rectangleShape->GetVertices(), pose, center, circleShpae->radius(), i_contact);
	}

	return isCollide;
}

bool IntersectCircle(const PhysicsVector2D i_centerA, const double i_radiusA, const PhysicsVector2D i_centerB, const double i_radiusB, Contact& i_contact)
{
	bool isIntersect = false;

	PhysicsVector2D normal = i_centerA - i_centerB;
	double distance = normal.GetLength();
	isIntersect = distance <= i_radiusA + i_radiusB;

	if (isIntersect)
	{
		i_contact.penetration = i_radiusA + i_radiusB - distance;
		i_contact.normal = normal.Normalize();
	}

	return isIntersect;
}

bool IntersectRectangle(std::vector<PhysicsVector2D> i_verticesA, const PhysicsVector2D i_poseA, std::vector<PhysicsVector2D> i_verticesB, const PhysicsVector2D i_poseB, Contact& i_contact)
{
	bool isIntersect = true;

	std::vector<PhysicsVector2D> axisList;
	// get axis for project
	for (int i = 0; i < 2; i++)
	{
		PhysicsVector2D vectorA = i_verticesA[i + 1] - i_verticesA[i];
		PhysicsVector2D vectorB = i_verticesB[i + 1] - i_verticesB[i];
		vectorA = vectorA.Normalize();
		vectorB = vectorB.Normalize();
		vectorA = PhysicsVector2D(-vectorA.y(), vectorA.x());
		vectorB = PhysicsVector2D(vectorB.y(), -vectorB.x());

		axisList.push_back(vectorA);
		axisList.push_back(vectorB);
	}

	// loop axis, compute penetraion and normal
	double penetraion = DBL_MAX;
	PhysicsVector2D normal;
	for (auto axis : axisList)
	{
		double minValueA, maxValueA, minValueB, maxValueB;
		ProjectPolygon(axis, i_verticesA, i_poseA, minValueA, maxValueA);
		ProjectPolygon(axis, i_verticesB, i_poseB, minValueB, maxValueB);
		double depth = std::min(maxValueA, maxValueB) - std::max(minValueA, minValueB);
		if (depth < 0)
			return false;

		if (penetraion > depth)
		{
			penetraion = depth;
			normal = axis;
		}
	}
	PhysicsVector2D v = i_poseA - i_poseB;
	if (v.DotProduct(normal) < 0)
		normal = -normal;

	i_contact.penetration = penetraion;
	i_contact.normal = normal;

	return isIntersect;
}

bool IntersectRectangleAndCircle(std::vector<PhysicsVector2D> i_vertices, const PhysicsVector2D i_pose, const PhysicsVector2D i_center, const double i_radius, Contact& i_contact)
{
	bool isIntersect = true;

	std::vector<PhysicsVector2D> axisList;
	// get axis for project
	for (int i = 0; i < 2; i++)
	{
		PhysicsVector2D vectorA = i_vertices[i + 1] - i_vertices[i];
		vectorA = vectorA.Normalize();
		vectorA = PhysicsVector2D(-vectorA.y(), vectorA.x());

		axisList.push_back(vectorA);
	}
	// find closest point on circle
	PhysicsVector2D closestPoint;
	double distance = DBL_MAX;
	for (auto vertice : i_vertices)
	{
		double len = (vertice + i_pose - i_center).GetLength();
		if (distance > len)
		{
			closestPoint = vertice + i_pose;
			distance = len;
		}
	}
	axisList.push_back((closestPoint - i_center).Normalize());

	// loop axis, compute penetraion and normal
	double penetraion = DBL_MAX;
	PhysicsVector2D normal;
	for (auto axis : axisList)
	{
		double minValueA, maxValueA, minValueB, maxValueB;
		ProjectPolygon(axis, i_vertices, i_pose, minValueA, maxValueA);
		ProjectCircle(axis, i_radius, i_center, minValueB, maxValueB);
		double depth = std::min(maxValueB - minValueA, maxValueA - minValueB);
		if (depth < 0)
			return false;

		if (penetraion > depth)
		{
			penetraion = depth;
			normal = axis;
		}
	}

	PhysicsVector2D v = i_pose - i_center;
	if(v.DotProduct(normal) < 0)
		normal = -normal;

	i_contact.penetration = penetraion;
	i_contact.normal = normal;

	return isIntersect;
}

void ProjectPolygon(const PhysicsVector2D i_axis, std::vector<PhysicsVector2D> i_vertices, const PhysicsVector2D i_pose, double& i_min, double& i_max)
{
	double minValue = DBL_MAX;
	double maxValue = -DBL_MAX;
	for (auto vertice : i_vertices)
	{
		PhysicsVector2D vec = vertice + i_pose;
		double value = vec.DotProduct(i_axis);
		minValue = value < minValue ? value : minValue;
		maxValue = value > maxValue ? value : maxValue;
	}

	i_min = minValue;
	i_max = maxValue;
}

void ProjectCircle(const PhysicsVector2D i_axis, const double i_radius, const PhysicsVector2D i_center, double& i_min, double& i_max)
{
	double dotValue = i_center.DotProduct(i_axis);
	i_min = dotValue - i_radius;
	i_max = dotValue + i_radius;
}