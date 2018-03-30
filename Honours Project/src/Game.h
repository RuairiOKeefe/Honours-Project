#pragma once
#include <vector>
#include <memory>
#include <chrono>

#include "btBulletDynamicsCommon.h"
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

	btDiscreteDynamicsWorld* dynamicsWorld;

public:

	btDiscreteDynamicsWorld* GetDynamicsWorld() { return dynamicsWorld; };
	inline btVector3 glm2bt(const glm::vec3& vec) { return { vec.x, vec.y, vec.z }; };
	inline glm::vec3 bt2glm(const btVector3& vec) { return glm::vec3( vec.getX(), vec.getY(), vec.getZ() ); };
	void Initialise();
	void Update();
	void Render();
};