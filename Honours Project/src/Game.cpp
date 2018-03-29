#include "Game.h"
#include "Entity.h"
#include "PointLight.h"

std::vector<Entity*> Game::entities;
double Game::lastTime;
glm::vec3 Game::windVector = glm::vec3(1,0,0);

btDiscreteDynamicsWorld* dynamicsWorld;

void Game::Initialise()
{
	free_cam = new Entity;
	auto cam = std::make_unique<Free_Camera>(glm::half_pi<float>());
	cam->SetPosition(glm::dvec3(10.0, 5.0, 50.0));
	cam->SetProjection(GameEngine::Get().GetScreenWidth() / GameEngine::Get().GetScreenHeight(), 2.414f, 1000);
	std::cout << GameEngine::Get().GetScreenHeight();
	free_cam->AddComponent(move(cam));

	Entity* tempEntity = new Entity;
	auto tempRenderable = std::make_unique<Renderable>();
	tempRenderable->SetModel("../res/models/Torus2.obj");
	tempRenderable->SetEffect("debug");
	tempEntity->SetPosition(glm::vec3(3.5f, 2.5f, 3.5f));
	tempRenderable->UpdateTransforms();

	tempEntity->AddComponent(move(tempRenderable));

	entities.push_back(tempEntity);

	Entity* tempEntity2 = new Entity;
	auto tempRenderable2 = std::make_unique<Renderable>();
	auto tempAerodynamics = std::make_unique<aerodynamics>("../res/models/Torus2.obj");
	tempRenderable2->SetCube(1);
	tempRenderable2->SetEffect("debug");
	tempEntity2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	tempRenderable2->UpdateTransforms();
	tempAerodynamics->GenerateSurfaceData();
	tempEntity2->AddComponent(move(tempAerodynamics));
	tempEntity2->AddComponent(move(tempRenderable2));

	entities.push_back(tempEntity2);

	windVector = glm::vec3(1, 1, 1);

	lastTime = clock();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
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
		//entities[n]->Rotate(glm::vec3(0.01f, 0.01f, 0.0f));
		entities[n]->Update(deltaTime);
		n++;
	}
	if (xflip)
		windVector.x -= deltaTime;
	else
		windVector.x += deltaTime;

	if (zflip)
		windVector.z -= deltaTime;
	else
		windVector.z += deltaTime;

	if (windVector.x > 1 || windVector.x < -1)
		xflip = !xflip;
	if (windVector.z > 1 || windVector.z < -1)
		zflip = !zflip;
	glm::normalize(windVector);

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