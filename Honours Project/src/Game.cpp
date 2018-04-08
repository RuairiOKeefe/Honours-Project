#include "Game.h"
#include "Entity.h"
#include "PointLight.h"

std::vector<Entity*> Game::entities;
double Game::lastTime;
glm::vec3 Game::windVector = glm::vec3(1, 0, 0);

btDiscreteDynamicsWorld* dynamicsWorld;

void Game::Initialise()
{
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));

	free_cam = new Entity;
	auto cam = std::make_unique<Free_Camera>(glm::half_pi<float>());
	cam->SetPosition(glm::dvec3(10.0, 5.0, 50.0));
	cam->SetProjection(GameEngine::Get().GetScreenWidth() / GameEngine::Get().GetScreenHeight(), 2.414f, 1000);
	std::cout << GameEngine::Get().GetScreenHeight();
	free_cam->AddComponent(move(cam));

	Entity* tempEntity = new Entity;
	auto tempRenderable = std::make_unique<Renderable>();
	tempRenderable->SetModel("../res/models/paper_airplane.obj");
	tempRenderable->SetEffect("debug");
	tempEntity->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	tempEntity->SetScale(glm::vec3(100));
	tempRenderable->UpdateTransforms();

	tempEntity->AddComponent(move(tempRenderable));

	entities.push_back(tempEntity);

	switch (0)
	{
	case(0):
	{
		Entity* tempEntity2 = new Entity;
		auto tempRenderable2 = std::make_unique<Renderable>();
		auto tempAerodynamics2 = std::make_unique<aerodynamics>("../res/models/4_sided.obj");
		tempRenderable2->SetModel("../res/models/4_sided.obj");
		tempRenderable2->SetEffect("debug");
		tempEntity2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity2->SetScale(glm::vec3(1));
		tempRenderable2->UpdateTransforms();
		tempAerodynamics2->UpdateTransforms();
		tempEntity2->AddComponent(move(tempAerodynamics2));
		tempEntity2->AddComponent(move(tempRenderable2));

		entities.push_back(tempEntity2);

		Entity* tempEntity3 = new Entity;
		auto tempRenderable3 = std::make_unique<Renderable>();
		auto tempAerodynamics3 = std::make_unique<aerodynamics>("../res/models/cube.obj");
		tempRenderable3->SetModel("../res/models/cube.obj");
		tempRenderable3->SetEffect("debug");
		tempEntity3->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity3->SetScale(glm::vec3(1));
		tempRenderable3->UpdateTransforms();
		tempAerodynamics3->UpdateTransforms();
		tempEntity3->AddComponent(move(tempAerodynamics3));
		tempEntity3->AddComponent(move(tempRenderable3));

		entities.push_back(tempEntity3);

		Entity* tempEntity4 = new Entity;
		auto tempRenderable4 = std::make_unique<Renderable>();
		auto tempAerodynamics4 = std::make_unique<aerodynamics>("../res/models/8_sided.obj");
		tempRenderable4->SetModel("../res/models/8_sided.obj");
		tempRenderable4->SetEffect("debug");
		tempEntity4->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity4->SetScale(glm::vec3(1));
		tempRenderable4->UpdateTransforms();
		tempAerodynamics4->UpdateTransforms();
		tempEntity4->AddComponent(move(tempAerodynamics4));
		tempEntity4->AddComponent(move(tempRenderable4));

		entities.push_back(tempEntity4);

		Entity* tempEntity5 = new Entity;
		auto tempRenderable5 = std::make_unique<Renderable>();
		auto tempAerodynamics5 = std::make_unique<aerodynamics>("../res/models/20_sided.obj");
		tempRenderable5->SetModel("../res/models/20_sided.obj");
		tempRenderable5->SetEffect("debug");
		tempEntity5->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity5->SetScale(glm::vec3(1));
		tempRenderable5->UpdateTransforms();
		tempAerodynamics5->UpdateTransforms();
		tempEntity5->AddComponent(move(tempAerodynamics5));
		tempEntity5->AddComponent(move(tempRenderable5));

		entities.push_back(tempEntity5);
	}
	break;
	case(1):
	{
		Entity* tempEntity2 = new Entity;
		auto tempRenderable2 = std::make_unique<Renderable>();
		auto tempAerodynamics = std::make_unique<aerodynamics>("../res/models/paper_airplane.obj");
		tempRenderable2->SetModel("../res/models/paper_airplane.obj");
		tempRenderable2->SetEffect("debug");
		tempEntity2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity2->SetScale(glm::vec3(100));
		tempRenderable2->UpdateTransforms();
		tempAerodynamics->UpdateTransforms();
		tempEntity2->AddComponent(move(tempAerodynamics));
		tempEntity2->AddComponent(move(tempRenderable2));

		entities.push_back(tempEntity2);
	}
	break;
	case(2):
	{
		Entity* tempEntity2 = new Entity;
		auto tempRenderable2 = std::make_unique<Renderable>();
		auto tempAerodynamics = std::make_unique<aerodynamics>("../res/models/paper_airplane.obj");
		tempRenderable2->SetModel("../res/models/paper_airplane.obj");
		tempRenderable2->SetEffect("debug");
		tempEntity2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity2->SetScale(glm::vec3(100));
		tempRenderable2->UpdateTransforms();
		tempAerodynamics->UpdateTransforms();
		tempEntity2->AddComponent(move(tempAerodynamics));
		tempEntity2->AddComponent(move(tempRenderable2));

		entities.push_back(tempEntity2);
	}
	break;
	case(3):
	{
		Entity* tempEntity2 = new Entity;
		auto tempRenderable2 = std::make_unique<Renderable>();
		auto tempAerodynamics = std::make_unique<aerodynamics>("../res/models/paper_airplane.obj");
		tempRenderable2->SetModel("../res/models/paper_airplane.obj");
		tempRenderable2->SetEffect("debug");
		tempEntity2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		tempEntity2->SetScale(glm::vec3(100));
		tempRenderable2->UpdateTransforms();
		tempAerodynamics->UpdateTransforms();
		tempEntity2->AddComponent(move(tempAerodynamics));
		tempEntity2->AddComponent(move(tempRenderable2));

		entities.push_back(tempEntity2);
	}
	break;
	}


	for (std::vector<Entity*>::size_type n = 0; n < entities.size();)
	{
		entities[n]->Init();
		n++;
	}
	windVector = glm::vec3(0, 0, 0);

	lastTime = clock();
	GameEngine::Get().SetupComputeShader();
}

void Game::Update()
{
	glm::mat4 camMatrix = free_cam->GetComponent<Free_Camera>().GetProjection() * free_cam->GetComponent<Free_Camera>().GetView();
	GameEngine::Get().SetCamera(camMatrix);
	double deltaTime = (clock() - lastTime) / CLOCKS_PER_SEC;
	lastTime = clock();
	free_cam->Update(deltaTime);

	dynamicsWorld->stepSimulation(deltaTime, 10);

	for (std::vector<Entity*>::size_type n = 0; n < entities.size();)
	{
		if (entities[n]->GetCompatibleComponent<aerodynamics>() != NULL)
		{
			btCollisionObject* collObj = dynamicsWorld->getCollisionObjectArray().at(entities[n]->GetCompatibleComponent<aerodynamics>()->GetIndex());
			btTransform t;
			float mat[16];
			t = collObj->getWorldTransform();
			t.getOpenGLMatrix(mat);
			entities[n]->SetTransform(btScalar2glmMat4(mat));
			if (toPush)
			{
				btRigidBody::upcast(collObj)->applyCentralForce(btVector3(0, 0, -1000));
			}
			//entities[n]
			printf("%f, ", btRigidBody::upcast(collObj)->getLinearVelocity().getY());
			printf("%f \n", btRigidBody::upcast(collObj)->getLinearVelocity().getZ());
		}
		//entities[n]->Rotate(glm::vec3(0.01f, 0.01f, 0.0f));
		entities[n]->Update(deltaTime);
		n++;
	}
	toPush = false;
	//	printf("%f.9\n", deltaTime);
}

void Game::Render()
{
	// Clear the opengl buffer.
	glClearColor(0.1, 0.0, 0.4, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_CULL_FACE);

//	GameEngine::Get().SetCameraPos(free_cam->GetPosition());
	GameEngine::Get().SetCameraPos(free_cam->GetComponent<Free_Camera>().GetPosition());
	GameEngine::Get().SetWindVector(windVector);

	for (std::vector<Entity*>::size_type n = 0; n < entities.size();)
	{
		entities[n]->Render();
		n++;
	}

	// process events.
	glfwPollEvents();
	// Swap the window buffers.
	glfwSwapBuffers(GameEngine::Get().GetWindow());
}