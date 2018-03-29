#include "aerodynamics.h"
#include "Game.h"

void aerodynamics::from_json(const nlohmann::json & j)
{
}

aerodynamics::aerodynamics() : Component("aerodynamics")
{
}

aerodynamics::aerodynamics(const std::string & fileName) : Component("aerodynamics"), Model(fileName)
{
}

aerodynamics::~aerodynamics()
{
}

void aerodynamics::GenerateSurfaceData() //Should be called after an aerodynamic model is created, only needs to be called once. Parallelisation isn't necessary, if it takes too long to generate consider however
{
	btTriangleMesh* mesh = new btTriangleMesh();

	int numverts = vertices.size();
	for (int i = 0; i < numverts; i + 3)
	{
		std::vector<Vertex> polyVerts;
		SurfaceData *tempSurface = new SurfaceData();
		for (int j = 0; j < 3; j++)
		{
			polyVerts.push_back(vertices[i + j]);
		}
		tempSurface->CalculateSurface(polyVerts);
		surfaceData.push_back(*tempSurface);
		polyVerts.clear();
		btVector3 v0, v1, v2;
		v0.x = vertices[i].position.x;
		v0.y = vertices[i].position.y;
		v0.z = vertices[i].position.z;

		v1.x = vertices[i + 1].position.x;
		v1.y = vertices[i + 1].position.y;
		v1.z = vertices[i + 1].position.z;

		v2.x = vertices[i + 2].position.x;
		v2.y = vertices[i + 2].position.y;
		v2.z = vertices[i + 2].position.z;

		mesh->addTriangle(v0, v1, v2);
	}
	index = Game::Get().GetDynamicsWorld()->getCollisionObjectArray().size();

	btTransform	trans;
	trans.setIdentity();

	btVector3 position;
	trans.setOrigin(position);

	btCollisionShape* trimeshShape = new btBvhTriangleMeshShape(mesh, false);

	btVector3 inertia;
	inertia.x = 0;
	inertia.y = 0;
	inertia.z = 0;

	trimeshShape->calculateLocalInertia(1, inertia);

	btDefaultMotionState* motionstate = new btDefaultMotionState(trans);

	btRigidBody* body = new btRigidBody(1, motionstate, trimeshShape, inertia);


	btCollisionObject* collisionObject = new btCollisionObject();

	collisionObject->setCollisionShape(trimeshShape);

	Game::Get().GetDynamicsWorld()->addCollisionObject(collisionObject);
	Game::Get().GetDynamicsWorld()->addRigidBody(body);
}

void aerodynamics::Update(const double delta)
{

	vec3 orientation = vec3(GetParent()->GetTransform()[2][0], 0, GetParent()->GetTransform()[2][2]); //may be reverse?
	for (int i = 0; i < surfaceData.size(); i++)
	{
		surfaceData[i].CalculateSurfaceAirflow(orientation, delta);
	}
}
