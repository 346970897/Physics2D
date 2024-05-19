#include <iostream>

#include<osgViewer/Viewer>
#include <osg/LineWidth>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/Optimizer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgGA/TrackballManipulator>

#include "PhysicsRendering.h"

// global parameter
osg::ref_ptr<osg::Group> root = nullptr;
osg::ref_ptr<osgViewer::Viewer> viewer = nullptr;
PhysicsWorld* physics_world = nullptr;
PhysicsBody* ground_body = nullptr;
PhysicsVector gravity(0, -980.0, 0); // gravity is along y
double time_step = 0.01;
int iteration = 1;

class SimulationCallback : public osg::NodeCallback
{
public:
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		if (physics_world)
			physics_world->Simulation(time_step, iteration);

		// Call base class update routine
		traverse(node, nv);
	}
};

class UpdateCallback : public osg::NodeCallback
{
public:

	UpdateCallback(PhysicsBody* body, osg::PositionAttitudeTransform* transform) :m_body(body), m_transform(transform) {};

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		if (m_body)
		{
			PhysicsTransform global_pose = m_body->GetGlobaPose();
			osg::Vec3 position(global_pose.GetPosition().x(), global_pose.GetPosition().y(), 0);
			osg::Quat rotation(global_pose.GetRotation().x(), global_pose.GetRotation().y(), global_pose.GetRotation().z(), global_pose.GetRotation().w());

			m_transform->setPosition(position);
			m_transform->setAttitude(rotation);
		}

		// Call base class update routine
		traverse(node, nv);
	}

private:

	PhysicsBody* m_body = nullptr;
	osg::PositionAttitudeTransform* m_transform = nullptr;
};

class NoMouseEventManipulator : public osgGA::TrackballManipulator
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
		{
			// create static ground body
			if (!ground_body)
			{
				double half_height = 10;
				double half_width = 150;
				osg::Vec3 position(0, -100, 0);
				osg::ref_ptr<osg::PositionAttitudeTransform> transform = PhysicsRendering::create_box(half_width, half_height, position);
				ground_body = PhysicsRendering::create_ground_body(half_width, half_height, PhysicsVector(position.x(), position.y(), 0));
				transform->setUpdateCallback(new UpdateCallback(ground_body, transform.get()));
				root->addChild(transform);
				physics_world->AddBody(ground_body);
			}
			// create dynamic body
			else if (viewer.valid())
			{
				osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
				if (camera.valid())
				{
					osg::Viewport* viewport = camera->getViewport();
					if (!viewport)
						return false;

					// computer world coordinates
					osg::Vec3d win(ea.getX(), ea.getY(), 0);
					osg::Matrix viewport_matrix = viewport->computeWindowMatrix();
					osg::Matrix proj_matrix = camera->getProjectionMatrix();
					osg::Matrix view_matrix = camera->getViewMatrix();
					osg::Matrix view_proj_matrix = view_matrix * proj_matrix * viewport_matrix;
					osg::Matrix inv_matrix;
					inv_matrix.invert(view_proj_matrix);
					osg::Vec3d world_coord = win * inv_matrix;

					int value = PhysicsRendering::get_random(0, 1);
					//value = 1;
					osg::Vec3 position(world_coord.x(), world_coord.y(), 0);
					osg::Quat rotation(0/*PI / 4*/, osg::Vec3(0, 0, 1));
					osg::ref_ptr<osg::PositionAttitudeTransform> transform = nullptr;
					PhysicsBody* body = nullptr;
					if (value == 0)
					{
						double radius = 10;
						transform = PhysicsRendering::create_circle(radius, position);
						body = PhysicsRendering::create_circle_body(radius, PhysicsVector(position.x(), position.y(), 0));
					}
					else
					{
						double half_height = 10;
						double half_width = 10;
						transform = PhysicsRendering::create_box(half_width, half_height, position);
						transform->setAttitude(rotation);
						PhysicsTransform pose;
						pose.SetPosition(PhysicsVector(position.x(), position.y(), 0));
						pose.SetRotation(PhysicsQuat(rotation.x(), rotation.y(), rotation.z(), rotation.w()));
						body = PhysicsRendering::create_box_body(half_width, half_height, pose);
					}

					transform->setUpdateCallback(new UpdateCallback(body, transform.get()));
					root->addChild(transform);
					physics_world->AddBody(body);
				}
			}
		}
		//return osgGA::TrackballManipulator::handle(ea, aa);
		return false;
	}
};

int main()
{
	// init scene
	viewer = PhysicsRendering::init_rendering();
	physics_world = PhysicsRendering::init_physics(gravity);
	root = new osg::Group();
	osg::ref_ptr<NoMouseEventManipulator> manipulator = new NoMouseEventManipulator;
	manipulator->setHomePosition(osg::Vec3(0, 0, 500), osg::Vec3(0, 0, 0), osg::Vec3(0, 1, 0));

	// simulation
	root->setUpdateCallback(new SimulationCallback());
	
	// start rendering
	PhysicsRendering::rendering(root, manipulator);
}


