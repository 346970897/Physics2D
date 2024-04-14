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

	double x() const;

	double y() const;

	double z() const;

	double w() const;

	double Magnitude();

	PhysicsQuat Conjugate() const;

	PhysicsVector operator*(const PhysicsVector v) const;

	PhysicsQuat operator*(const PhysicsQuat q) const;

	PhysicsQuat& operator*=(const PhysicsQuat q);


private:

	double m_x = 0;
	double m_y = 0;
	double m_z = 0;
	double m_w = 1;
};

#endif //  PHYSICS_QUATERNION

