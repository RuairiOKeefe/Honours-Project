#include "aerodynamics.h"
#include "Game.h"
#include "GameEngine.h"

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

	int numVerts = vertices.size();
	for (int i = 0; i < numVerts - 2; i += 3)//check this
	{
		std::vector<Vertex> polyVerts;
		SurfaceData *tempSurface = new SurfaceData();
		for (int j = 0; j < 3; j++)
		{
			if (i + j < numVerts)
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

	for (int i = 0; i < surfaceData.size(); i++)
	{
		vec3 vertices[3];
		for (int j = 0; j < 3; j++)
			vertices[j] = surfaceData[i].vertices[j].position;
		verticesVec.push_back(vertices);
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

	Game::Get().GetDynamicsWorld()->addRigidBody(body);
}

void aerodynamics::Update(const double delta)
{
	btCollisionObject* collObj = Game::Get().GetDynamicsWorld()->getCollisionObjectArray()[index];
	vec3 orientation = vec3(GetParent()->GetTransform()[2][0], 0, GetParent()->GetTransform()[2][2]); //may be reverse?
	btVector3 origin = Game::Get().glm2bt(GetParent()->GetPosition());
	mat4 trans = GetParent()->GetTransform();
	vec3 linearVel = Game::Get().bt2glm(btRigidBody::upcast(collObj)->getLinearVelocity());
	vec3 angularVel = Game::Get().bt2glm(btRigidBody::upcast(collObj)->getAngularVelocity());
	vec3 windVec = Game::Get().GetWindVector();
	if (true)
	{
		for (int i = 0; i < surfaceData.size(); i++)
		{
			vec3 vertices[3];
			for (int j = 0; j < 3; j++)
				vertices[j] = verticesVec[i][j];
			vec3 force = surfaceData[i].CalculateSurfaceAirflow(trans, vertices, surfaceData[i].area, surfaceData[i].normal, surfaceData[i].center, surfaceData[i].vertexWeights, linearVel, angularVel, windVec);
			btRigidBody::upcast(collObj)->applyForce(Game::Get().glm2bt(force), origin + Game::Get().glm2bt(surfaceData[i].center));
		}
	}
	else
	{
		GameEngine::Get().SetupComputeShader();
		vec3 *force = GameEngine::Get().InvokeComputeShader(trans, surfaceData, linearVel, angularVel, windVec);
		for (int i = 0; i < surfaceData.size(); i++)
		{
			btRigidBody::upcast(collObj)->applyForce(Game::Get().glm2bt(force[i]), origin + Game::Get().glm2bt(surfaceData[i].center));
		}
	}
}
