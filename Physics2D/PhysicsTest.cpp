#include "iostream"
#include "PhysicsWorld.h"

int main()
{
	// cerate physical world
	PhysicsWorld* world = PhysicsWorld::CreatePhysicsWorld();

	// create ground plane(static body)
	StaticBody* ground_plane = new StaticBody(PhysicsVector2D(0, 0));
	RectangleShape* ground_shape = new RectangleShape(100, 10);
	ground_plane->AddShape(ground_shape);

	//// create dynamic body
	//DynamicBody* circle_body = new DynamicBody(PhysicsVector2D(0, 30), 1.0);
	//CircleShape* circle_shape = new CircleShape(10);
	//circle_body->AddShape(circle_shape);
	//circle_body->UpdateMass();
	DynamicBody* rect_body = new DynamicBody(PhysicsVector2D(0, 100), 1.0);
	RectangleShape* rect_shape = new RectangleShape(10, 10);
	rect_body->AddShape(rect_shape);
	rect_body->UpdateMass();

	// add body to world
	world->AddBody(ground_plane);
	world->AddBody(rect_body);

	while (true)
	{
		world->Simulation(0.01);
		for (auto body : world->GetBodies())
		{
			PhysicsVector2D pose = body->GetGlobaPose();
			std::cout << "pose:  " << pose.x() << "  " << pose.y() << std::endl;
			int a = 0;
		}
	}

}