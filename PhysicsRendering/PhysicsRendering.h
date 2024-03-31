#ifndef PHYSICS_RENDERING_H
#define PHYSICS_RENDERING_H

// OSG
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
// PHYSICS
#include "PhysicsWorld.h"

class PhysicsRendering
{
public:

	static osg::ref_ptr<osgViewer::Viewer> init_rendering();

	static PhysicsWorld* init_physics(const PhysicsVector2D gravity = PhysicsVector2D(0, -980));

	static void rendering(const osg::ref_ptr<osg::Group> root, osg::ref_ptr<osgGA::CameraManipulator> manipulator);

	static osg::ref_ptr<osg::PositionAttitudeTransform> create_circle(const double radius, const osg::Vec3 pose, int num_segment = 30);

	static osg::ref_ptr<osg::PositionAttitudeTransform> create_box(const double half_height, const double half_width, const osg::Vec3 pose);
	
	static PhysicsBody* create_circle_body(const double radius, const PhysicsVector2D pose);
	
	static PhysicsBody* create_ground_body(const double half_height, const double half_width, const PhysicsVector2D pose);
	
	static PhysicsBody* create_box_body(const double half_width, const double half_height, const PhysicsVector2D pose);

	static int get_random(const int min_value, const int max_value);

	static double get_random(const double min_value, const double max_value);

private:	

	PhysicsRendering();

	~PhysicsRendering();
	
};

#endif 