#ifndef PHYSICS_VECTOR2D
#define PHYSICS_VECTOR2D

class PhysicsVector2D
{
public:

	PhysicsVector2D();

	PhysicsVector2D(const double x, const double y);

	~PhysicsVector2D();

	double& x();

	double& y();

	double DotProduct(const PhysicsVector2D v1) const;

	double GetLength();

	double GetLengthSquared();

	PhysicsVector2D Normalize() const;

	PhysicsVector2D operator+(const PhysicsVector2D v) const;

	PhysicsVector2D operator-(const PhysicsVector2D v) const;

	PhysicsVector2D operator-() const;

	PhysicsVector2D operator*(const double value) const;

	void operator=(const PhysicsVector2D value);

private:

	double m_x = 0.0;
	double m_y = 0.0;
};


#endif // !PHYSICS_VECTOR2D

