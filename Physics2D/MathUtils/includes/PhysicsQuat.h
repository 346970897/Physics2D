#ifndef  PHYSICS_QUATERNION
#define PHYSICS_QUATERNION

#include "PhysicsVector.h"

class PhysicsQuat
{

public:

	PhysicsQuat(const double x, const double y, const double z, const double w);

	PhysicsQuat(PhysicsVector v, const double w);

	PhysicsQuat();

	~PhysicsQuat();

	double& x();

	double& y();

	double& z();

	double& w();

	double Magnitude();

	PhysicsQuat Normalize();

	PhysicsQuat Conjugate() const;

	PhysicsVector MakeRotation(const PhysicsVector v) const;

	void GetRotate(PhysicsVector& axis, double& angle) const;

	PhysicsVector MakeEulerAngles() const;

	void ToRotationMatrix(double matrix[3][3]) const;

	PhysicsQuat operator*(const PhysicsQuat q) const;

	PhysicsQuat& operator*=(const PhysicsQuat q);

	PhysicsQuat operator+(const PhysicsQuat q) const;

	PhysicsQuat& operator+=(const PhysicsQuat q);

	PhysicsQuat operator/(const double value) const;

	PhysicsQuat& operator/=(const double value);

private:

	double m_x = 0;
	double m_y = 0;
	double m_z = 0;
	double m_w = 1;
};

#endif //  PHYSICS_QUATERNION

