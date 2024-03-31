#include "Contact.h"
#include <DynamicBody.h>

Contact::Contact()
{

}

Contact::~Contact()
{
}

void Contact::resolve()
{
    if (bodyA->GetBodyType() & BodyType::STATIC_BODY && bodyB->GetBodyType() & BodyType::STATIC_BODY)
        return;

    resolvePenetraion();
    resolveVelocity();
}

void Contact::resolvePenetraion() const
{
    if ((bodyA->GetBodyType() & BodyType::DYNAMIC_BODY) != 0 && bodyA->GetShape()->GetShapeType() & ShapeType::RECTANGLE_SHAPE && bodyB->GetShape()->GetShapeType() & ShapeType::CIRCLE_SHAPE)
    {
        int a = 0;
    }
    double totalInverseMass = bodyA->GetInvMass() + bodyB->GetInvMass();
    PhysicsVector2D movePoseA = normal * (penetration * bodyA->GetInvMass() / totalInverseMass);
    PhysicsVector2D movePoseB = -normal * (penetration * bodyB->GetInvMass() / totalInverseMass);

    if(bodyA->GetBodyType() & BodyType::DYNAMIC_BODY)
        dynamic_cast<DynamicBody*>(bodyA)->MoveTo(movePoseA);
    if (bodyB->GetBodyType() & BodyType::DYNAMIC_BODY)
        dynamic_cast<DynamicBody*>(bodyB)->MoveTo(movePoseB);
}

void Contact::resolveVelocity() const
{
    PhysicsVector2D relativeLinearVel = bodyB->GetLinearVelocity() - bodyA->GetLinearVelocity();
    double e = std::min(shapeA->GetRestitution(), shapeB->GetRestitution());
    double lambda = -(1.0 + e) * relativeLinearVel.DotProduct(normal);
    lambda /= (bodyA->GetInvMass() + bodyB->GetInvMass());
    PhysicsVector2D linearVelA = -normal * lambda * bodyA->GetInvMass();
    PhysicsVector2D linearVelB = normal * lambda * bodyB->GetInvMass();

    bodyA->AddLinearVelocity(linearVelA);
    bodyB->AddLinearVelocity(linearVelB);
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