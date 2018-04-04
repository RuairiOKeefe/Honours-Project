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

void aerodynamics::Init()
{
	GenerateSurfaceData();
}

void aerodynamics::GenerateSurfaceData() //Should be called after an aerodynamic model is created, only needs to be called once. Parallelisation isn't necessary, if it takes too long to generate consider however
{
	btTriangleMesh* mesh = new btTriangleMesh();

	int numverts = vertices.size();
	for (int i = 0; i < numverts - 2; i += 3)//check this
	{
		std::vector<Vertex> polyVerts;
		SurfaceData *tempSurface = new SurfaceData();
		for (int j = 0; j < 3; j++)
		{
			if (i + j < numverts)
				polyVerts.push_back(vertices[i + j]);
			else
				polyVerts.push_back(vertices[0]);
		}
		tempSurface->CalculateSurface(polyVerts);
		surfaceData.push_back(*tempSurface);
		polyVerts.clear();
		btVector3 v0, v1, v2;

		v0 = btVector3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
		v1 = btVector3(vertices[i + 1].position.x, vertices[i + 1].position.y, vertices[i + 1].position.z);
		v2 = btVector3(vertices[i + 2].position.x, vertices[i + 2].position.y, vertices[i + 2].position.z);

		mesh->addTriangle(v0, v1, v2);
	}
	index = Game::Get().GetDynamicsWorld()->getCollisionObjectArray().size();

	btTransform	trans;
	trans.setIdentity();

	vec3 p = vec3(GetParent()->GetPosition());
	btVector3 position = Game::Get().glm2bt(p);
	trans.setOrigin(position);

	btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(mesh, false);

	btVector3 inertia = btVector3(0.0, 0.0, 0.0);

	btScalar scalar = 1.0;
	trimeshShape->calculateLocalInertia(scalar, inertia);//Throws an error in debug

	btDefaultMotionState* motionstate = new btDefaultMotionState(trans);

	btRigidBody* body = new btRigidBody(4000000, motionstate, trimeshShape, inertia);

	btCollisionObject* collisionObject = new btCollisionObject();

	collisionObject->setCollisionShape(trimeshShape);

	//Game::Get().GetDynamicsWorld()->addCollisionObject(collisionObject);
	Game::Get().GetDynamicsWorld()->addRigidBody(body);
}

void aerodynamics::Update(const double delta)
{
	btCollisionObject* collObj = Game::Get().GetDynamicsWorld()->getCollisionObjectArray()[index];
	vec3 orientation = vec3(GetParent()->GetTransform()[2][0], 0, GetParent()->GetTransform()[2][2]); //may be reverse?
	btVector3 origin = Game::Get().glm2bt(GetParent()->GetPosition());
	for (int i = 0; i < surfaceData.size(); i++)
	{
		surfaceData[i].CalculateSurfaceAirflow(origin, orientation, delta, *collObj);
	}
}
