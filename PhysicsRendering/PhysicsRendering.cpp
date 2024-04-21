#include <Windows.h>
#include <iostream>
#include <random>

#include <osg/LineWidth>
#include <osgUtil/Optimizer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/ShapeDrawable>
#include <osg/Material>

#include "PhysicsRendering.h"


static osg::ref_ptr<osgViewer::Viewer> m_viewer;

static PhysicsWorld* m_world;

PhysicsRendering::~PhysicsRendering()
{
}

osg::ref_ptr<osgViewer::Viewer> PhysicsRendering::init_rendering()
{
	if (!m_viewer)
	{
		m_viewer = new osgViewer::Viewer();
		m_viewer->setUpViewInWindow(600, 100, 1200, 800);
	}

	return m_viewer;
}

PhysicsWorld* PhysicsRendering::init_physics(const PhysicsVector gravity)
{	
	if (!m_world)
		m_world = PhysicsWorld::CreatePhysicsWorld(gravity);

	return m_world;
}

void PhysicsRendering::rendering(const osg::ref_ptr<osg::Group> root, osg::ref_ptr < osgGA::CameraManipulator> manipulator)
{
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root);
	m_viewer->setSceneData(root.get());
	m_viewer->setCameraManipulator(manipulator.get());
	m_viewer->realize();
	m_viewer->run();
}

osg::ref_ptr<osg::PositionAttitudeTransform> PhysicsRendering::create_circle(const double radius, const osg::Vec3 pose, int num_segment)
{
	osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
	transform->setPosition(pose);
	osg::ref_ptr<osg::Geode> box = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> vertice_list = new osg::Vec3Array();
	for (int i = 0; i < num_segment; ++i)
	{
		float angle = 2.0f * PI * i / num_segment;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		vertice_list->push_back(osg::Vec3(x, y, 0.0f));
	}

	osg::ref_ptr<osg::Vec4Array> color_list = new osg::Vec4Array();
	color_list->push_back(osg::Vec4(get_random(0.0, 1.0), get_random(0.0, 1.0), get_random(0.0, 1.0), 1));

	osg::ref_ptr<osg::PrimitiveSet> primitive_set = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, vertice_list.get()->size());

	geometry->setVertexArray(vertice_list);
	geometry->setColorArray(color_list);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	geometry->addPrimitiveSet(primitive_set);

	box->addDrawable(geometry);
	transform->addChild(box);

	geometry.release();
	primitive_set.release();
	vertice_list.release();
	color_list.release();

	return transform;
}

osg::ref_ptr<osg::PositionAttitudeTransform> PhysicsRendering::create_box(const double half_width, const double half_height, const osg::Vec3 pose)
{
	osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
	transform->setPosition(pose);
	osg::ref_ptr<osg::Geode> box = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> vertice_list = new osg::Vec3Array();
	vertice_list->push_back(osg::Vec3(half_width, half_height, 0));
	vertice_list->push_back(osg::Vec3(-half_width, half_height, 0));
	vertice_list->push_back(osg::Vec3(-half_width, -half_height, 0));
	vertice_list->push_back(osg::Vec3(half_width, -half_height, 0));

	osg::ref_ptr<osg::Vec4Array> color_list = new osg::Vec4Array();
	color_list->push_back(osg::Vec4(get_random(0.0, 1.0), get_random(0.0, 1.0), get_random(0.0, 1.0), 1));

	osg::ref_ptr<osg::PrimitiveSet> primitive_set = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertice_list.get()->size());

	geometry->setVertexArray(vertice_list);
	geometry->setColorArray(color_list);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	geometry->addPrimitiveSet(primitive_set);

	box->addDrawable(geometry);
	transform->addChild(box);

	geometry.release();
	primitive_set.release();
	vertice_list.release();
	color_list.release();

	return transform;
}

PhysicsBody* PhysicsRendering::create_circle_body(const double radius, const PhysicsVector pose)
{
	CircleShape* circle_shape = new CircleShape(radius);
	DynamicBody* circle_body = new DynamicBody(pose, 1.0); 
	circle_body->AddShape(circle_shape);
	circle_body->UpdateMassAndInertia();

	return circle_body;
}

PhysicsBody* PhysicsRendering::create_ground_body(const double half_width, const double half_height, const PhysicsVector pose)
{
	RectangleShape* ground_shape = new RectangleShape(half_width, half_height);
	StaticBody* ground_body = new StaticBody(pose);
	ground_body->AddShape(ground_shape);

	return ground_body;
}

PhysicsBody* PhysicsRendering::create_box_body(const double half_width, const double half_height, const PhysicsVector pose)
{
	RectangleShape* box_shape = new RectangleShape(half_width, half_height);
	DynamicBody* box_body = new DynamicBody(pose, 1);
	box_body->AddShape(box_shape);
	box_body->UpdateMassAndInertia();

	return box_body;
}

int PhysicsRendering::get_random(const int min_value, const int max_value)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min_value, max_value);
	int value = dis(gen);

	return value;
}

double PhysicsRendering::get_random(const double min_value, const double max_value)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min_value, max_value);
	double value = dis(gen);

	return value;
}

