#include "DynamicBody.h"

DynamicBody::DynamicBody(const PhysicsTransform globalPose, const double density)
{
	m_bodyType = BodyType::DYNAMIC_BODY;
	m_globaPose = globalPose;
	m_density = density;
}

DynamicBody::~DynamicBody()
{
}

double DynamicBody::GetMass() const
{
	return m_mass;
}

void DynamicBody::SetMass(const double mass)
{
	if (mass >= Epsilon)
	{
		m_mass = mass;
		m_invMass = 1 / m_mass;
	}
}

double DynamicBody::GetInertia() const
{
	return m_inertia;
}

void DynamicBody::SetInertia(const double inertia)
{
	if (inertia >= Epsilon)
	{
		m_inertia = inertia;
		m_invInertia = 1 / m_inertia;
	}
}

void DynamicBody::UpdateMassAndInertia()
{
	if (!m_shape)
		return;

	double mass = m_density * m_shape->GetArea();
	if (mass >= Epsilon)
	{
		m_mass = mass;
		m_invMass = 1 / m_mass;
	}

	double inertia = 0;
	if (m_shape->GetShapeType() & ShapeType::CIRCLE_SHAPE)
	{
		CircleShape* shape = dynamic_cast<CircleShape*>(m_shape);
		double radius = shape->radius();
		inertia = 1.0 / 2.0 * m_mass * (radius * radius);
	}
	else if (m_shape->GetShapeType() & ShapeType::RECTANGLE_SHAPE)
	{
		RectangleShape* shape = dynamic_cast<RectangleShape*>(m_shape);
		double height = shape->height();
		double width = shape->width();
		inertia = 1.0 / 12.0 * m_mass * (height * height + width * width);
	}

	m_inertia = inertia;
	m_invInertia = 1 / m_inertia;
}

void DynamicBody::MoveTo(const PhysicsTransform pose)
{
	m_globaPose = m_globaPose * pose;
}

void DynamicBody::Simulation(const double time, const PhysicsVector gravity, const int iterator)
{
	double stepTime = time / iterator;
	PhysicsVector m_linearAccele = gravity + m_force * m_invMass;
	PhysicsVector m_angularAccle = m_torque * m_invInertia;
	m_linearVelocity += m_linearAccele * stepTime;
	m_angularVelocity += m_angularAccle * stepTime;

	PhysicsVector position = m_globaPose.GetPosition() + m_linearVelocity * stepTime;
	PhysicsVector q = m_angularVelocity * stepTime * 0.5;
	PhysicsQuat rotation = m_globaPose.GetRotation() + PhysicsQuat(q, 0) * m_globaPose.GetRotation();
	if (rotation.Magnitude() < Epsilon)
		rotation = PhysicsQuat();
	rotation = rotation.Normalize();
	m_globaPose = PhysicsTransform(position, rotation);

	m_force = PhysicsVector();
	m_torque = PhysicsVector();
}

