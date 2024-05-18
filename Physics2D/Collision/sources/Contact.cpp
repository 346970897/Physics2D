#include "Contact.h"
#include <DynamicBody.h>

Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::Resolve()
{
	if (!bodyA || !bodyB || !shapeA || !shapeB)
		return;
	if (bodyA->GetBodyType() & BodyType::STATIC_BODY && bodyB->GetBodyType() & BodyType::STATIC_BODY)
		return;

	ResolvePenetration();
	ResolveContactPoint();
	ResolveVelocity();
}

void Contact::ResolvePenetration() const
{
	double totalInverseMass = bodyA->GetInvMass() + bodyB->GetInvMass();
	PhysicsVector movePoseA = normal * (penetration * bodyA->GetInvMass() / totalInverseMass);
	PhysicsVector movePoseB = -normal * (penetration * bodyB->GetInvMass() / totalInverseMass);

	if (bodyA->GetBodyType() & BodyType::DYNAMIC_BODY)
		dynamic_cast<DynamicBody*>(bodyA)->MoveTo(movePoseA);
	if (bodyB->GetBodyType() & BodyType::DYNAMIC_BODY)
		dynamic_cast<DynamicBody*>(bodyB)->MoveTo(movePoseB);
}

void Contact::ResolveContactPoint()
{
	if (collideType & CollideType::CircleVsCircle)
		FindPointInCircles();
	else if (collideType & CollideType::RectangleVsCircle)
		FindPointInPolygonAndCircle();
	else if (collideType & CollideType::RectangleVsRectangle)
		FindPointInPolygons();
}

void Contact::ResolveVelocity() const
{
	double e = std::min(shapeA->GetRestitution(), shapeB->GetRestitution());
	PhysicsVector relativeLinearVel = bodyB->GetLinearVelocity() - bodyA->GetLinearVelocity();
	double lambda = -(1.0 + e) * relativeLinearVel.DotProduct(normal);
	lambda /= (bodyA->GetInvMass() + bodyB->GetInvMass());

	// compute linear velocity
	PhysicsVector linearVelA = -normal * lambda * bodyA->GetInvMass();
	PhysicsVector linearVelB = normal * lambda * bodyB->GetInvMass();
	// compute angular velocity
	PhysicsVector point;
	for (auto p : contactPoint)
	{
		point += p;
	}
	point /= std::max((int)contactPoint.size(), 1);
	PhysicsVector r1 = point - bodyA->GetGlobaPose().GetPosition();
	PhysicsVector r2 = point - bodyB->GetGlobaPose().GetPosition();
	PhysicsVector angluarVelA = (r1.CrossProduct(-normal * lambda)) * bodyA->GetInvInertia();
	PhysicsVector angluarVelB = (r2.CrossProduct(normal * lambda)) * bodyB->GetInvInertia();

	// apply velocity
	bodyA->AddLinearVelocity(linearVelA);
	bodyB->AddLinearVelocity(linearVelB);
	bodyA->AddAngularVelocity(angluarVelA);
	bodyB->AddAngularVelocity(angluarVelB);
}

void Contact::FindPointInCircles()
{
	PhysicsTransform pose = bodyA->GetGlobaPose();
	CircleShape* shape = dynamic_cast<CircleShape*>(shapeA);
	PhysicsVector offset = -normal * shape->radius();

	contactPoint.push_back(pose.GetPosition() + offset);
}

void Contact::FindPointInPolygonAndCircle()
{
	PhysicsTransform pose = bodyB->GetGlobaPose();
	CircleShape* shape = dynamic_cast<CircleShape*>(shapeB);
	PhysicsVector offset = normal * shape->radius();

	contactPoint.push_back(pose.GetPosition() + offset);
}

void Contact::FindPointInPolygons()
{
	// find edge that perpendicular to normal
	std::vector<PhysicsVector> edgesA;
	PhysicsTransform poseA = bodyA->GetGlobaPose();
	RectangleShape* rectShapeA = dynamic_cast<RectangleShape*>(shapeA);
	if (rectShapeA)
	{
		int n = rectShapeA->GetVertices().size();
		for (int i = 0; i < n; i++)
		{
			PhysicsVector point1 = rectShapeA->GetVertices()[i];
			PhysicsVector point2 = rectShapeA->GetVertices()[(i + 1) % n];
			point1 = poseA * point1;
			point2 = poseA * point2;
			PhysicsVector edge = point2 - point1;
			edge = edge.Normalize();
			if (std::abs(edge.DotProduct(normal)) < Epsilon)
			{
				edgesA.push_back(point1);
				edgesA.push_back(point2);
			}
		}
	}
	std::vector<PhysicsVector> edgesB;
	PhysicsTransform poseB = bodyB->GetGlobaPose();
	RectangleShape* rectShapeB = dynamic_cast<RectangleShape*>(shapeB);
	if (rectShapeB)
	{
		int n = rectShapeB->GetVertices().size();
		for (int i = 0; i < n; i++)
		{
			PhysicsVector point1 = rectShapeB->GetVertices()[i];
			PhysicsVector point2 = rectShapeB->GetVertices()[(i + 1) % n];
			point1 = poseB * point1;
			point2 = poseB * point2;
			PhysicsVector edge = point2 - point1;
			edge = edge.Normalize();
			if (std::abs(edge.DotProduct(normal)) < Epsilon)
			{
				edgesB.push_back(point1);
				edgesB.push_back(point2);
			}

		}
	}

	// if there are intersecting edges
	for (int i = 0; i < edgesA.size(); i += 2)
	{
		PhysicsVector pointA1 = edgesA[i];
		PhysicsVector pointA2 = edgesA[i + 1];
		PhysicsVector edgeA = pointA2 - pointA1;
		double dotValue = edgeA.DotProduct(edgeA);
		edgeA = edgeA.Normalize();
		for (int j = 0; j < edgesB.size(); j += 2)
		{
			PhysicsVector pointB1 = edgesB[j];
			PhysicsVector pointB2 = edgesB[j + 1];
			PhysicsVector edgeB = pointB2 - pointB1;
			edgeB = edgeB.Normalize();
			double value = std::abs(edgeA.DotProduct(edgeB));
			if (std::abs(value - 1) < Epsilon)
			{			
				PhysicsVector edge = pointB1 - pointA1;
				bool lower = edge.DotProduct(edgeA) > 0 && edge.DotProduct(edgeA) < dotValue;
				edge = pointB2 - pointA1;
				bool upper = edge.DotProduct(edgeA) > 0 && edge.DotProduct(edgeA) < dotValue;
				if (lower && upper)
				{
					contactPoint.push_back(pointB1);
					contactPoint.push_back(pointB2);
				}
				else if (!lower && upper)
				{
					contactPoint.push_back(pointB2);
					if(value > 0)
						contactPoint.push_back(pointA1);
					else
						contactPoint.push_back(pointA2);
				}
				else if (lower && !upper)
				{
					contactPoint.push_back(pointB1);
					if (value > 0)
						contactPoint.push_back(pointA2);
					else
						contactPoint.push_back(pointA1);
				}
				else if (!lower && !upper)
				{
					contactPoint.push_back(pointA1);
					contactPoint.push_back(pointA2);
				}

				return;
			}
		}
	}

	// there is the point on line
	for (auto point : edgesA)
	{
		for (int i = 0; i < edgesB.size(); i += 2)
		{
			PhysicsVector edge = edgesB[i] - edgesB[i + 1];
			double value = edge.DotProduct(edge);
			double dotValue = (point - edgesB[i]).DotProduct(edge);
			if (dotValue >= 0 && dotValue <= value)
			{
				contactPoint.push_back(point);
				return;
			}
		}
	}
	for (auto point : edgesB)
	{
		for (int i = 0; i < edgesA.size(); i += 2)
		{
			PhysicsVector edge = edgesA[i] - edgesA[i + 1];
			double value = edge.DotProduct(edge);
			double dotValue = (point - edgesA[i]).DotProduct(edge);
			if (dotValue >= 0 && dotValue <= value)
			{
				contactPoint.push_back(point);
				return;
			}
		}
	}
}

//void Contact::resolveVelocity()
//{
//    if (point1 == nullptr) return;
//    if (point2 == nullptr)
//    {
//        point2 = point1;
//    }
//
//    FlatVector impulseAlongNormal1 = normal * calculateImpulseAtPoint(*point1, normal) * 0.5f;
//    FlatVector impulseAlongNormal2 = normal * calculateImpulseAtPoint(*point2, normal) * 0.5f;
//
//    FlatVector normalPerp = normal.getPerpendicular();
//    FlatVector friction1 = normalPerp * calculateImpulseAtPoint(*point1, normalPerp) * 0.5f * 0.1f;
//    FlatVector friction2 = normalPerp * calculateImpulseAtPoint(*point2, normalPerp) * 0.5f * 0.1f;
//
//    bodyA->applyImpulse((impulseAlongNormal1 + friction1) * -1, *point1);
//    bodyA->applyImpulse((impulseAlongNormal2 + friction2) * -1, *point2);
//
//    bodyB->applyImpulse(impulseAlongNormal1 + friction1, *point1);
//    bodyB->applyImpulse(impulseAlongNormal2 + friction2, *point2);
//}
//
//float Contact::calculateImpulseAtPoint(const FlatVector& point, const FlatVector& contactNormal) const
//{
//    float restitution = std::min(bodyA->restitution, bodyB->restitution);
//
//    FlatVector rAPerpendicular = (point - bodyA->position).getPerpendicular();
//    FlatVector velocityA = bodyA->linearVelocity + rAPerpendicular * bodyA->angularVelocity;
//
//    FlatVector rBPerpendicular = (point - bodyB->position).getPerpendicular();
//    FlatVector velocityB = bodyB->linearVelocity + rBPerpendicular * bodyB->angularVelocity;
//
//    FlatVector relativeVelocity = velocityB - velocityA;
//
//    float impulse = -(1 + restitution) * relativeVelocity.dotProduct(contactNormal) /
//        ((bodyA->inverseMass + bodyB->inverseMass) +
//            (rAPerpendicular.dotProduct(contactNormal) * rAPerpendicular.dotProduct(contactNormal) *
//                bodyA->inverseInertia) +
//            (rBPerpendicular.dotProduct(contactNormal) * rBPerpendicular.dotProduct(contactNormal) *
//                bodyB->inverseInertia));
//
//    return impulse;
//}