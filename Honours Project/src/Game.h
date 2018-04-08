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
	bool toPush = true;
	int test;

	btDiscreteDynamicsWorld* dynamicsWorld;

public:

	vec3 GetWindVector() { return windVector; };
	btDiscreteDynamicsWorld* GetDynamicsWorld() { return dynamicsWorld; };
	inline btVector3 glm2bt(const glm::vec3& vec) { return { vec.x, vec.y, vec.z }; };
	inline glm::vec3 bt2glm(const btVector3& vec) { return glm::vec3( vec.getX(), vec.getY(), vec.getZ() ); };

	inline glm::mat4 btScalar2glmMat4(btScalar* matrix) {
		return glm::mat4(
			matrix[0], matrix[1], matrix[2], matrix[3],
			matrix[4], matrix[5], matrix[6], matrix[7],
			matrix[8], matrix[9], matrix[10], matrix[11],
			matrix[12], matrix[13], matrix[14], matrix[15]);
	}

	void Initialise();
	void Update();
	void Render();
};