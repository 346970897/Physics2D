#ifndef PHYSICS_VECTOR
#define PHYSICS_VECTOR

class PhysicsVector
{
public:

	PhysicsVector();

	PhysicsVector(const double value);

	PhysicsVector(const double x, const double y, const double z);

	~PhysicsVector();

	double& x();

	double& y();

	double& z();

	double DotProduct(const PhysicsVector v) const;

	PhysicsVector CrossProduct(const PhysicsVector v) const;

	double GetLength();

	double GetLengthSquared();

	PhysicsVector Normalize();

	PhysicsVector operator+(const PhysicsVector v) const;

	PhysicsVector& operator+=(const PhysicsVector v);

	PhysicsVector operator-(const PhysicsVector v) const;

	PhysicsVector& operator-=(const PhysicsVector v);

	PhysicsVector operator-() const;

	PhysicsVector operator*(const double value) const;

	PhysicsVector& operator*=(const double value);

	PhysicsVector operator/(const double value) const;

	PhysicsVector& operator/=(const double value);

	void operator=(const PhysicsVector value);

private:

	double m_x = 0.0;
	double m_y = 0.0;
	double m_z = 0.0;
};


#endif // !PHYSICS_VECTOR2D

