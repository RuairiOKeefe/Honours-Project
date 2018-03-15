#pragma once
#include <vector>
#include <memory>
#include <chrono>

#include "Singleton.h"
#include "GameEngine.h"
#include "Free_Camera.h"
#include "Renderable.h"
#include "aerodynamics.h"

class Entity;

class Game : public Singleton<Game>
{
private:
	Entity *free_cam = new Entity;
	static std::vector<Entity*> entities;//Figure out how to split this.
	static double lastTime;
	static glm::vec3 windVector;
	bool xflip = false;
	bool zflip = true;

public:

	void Initialise();
	void Update();
	void Render();
};