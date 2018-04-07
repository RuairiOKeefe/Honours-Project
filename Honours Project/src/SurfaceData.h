#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <string>
#include <vector>
#include <map>
#include "Model.h"
#include "btBulletDynamicsCommon.h"

using namespace glm;
class SurfaceData
{
public:
	float area;
	vec3 normal;
	vec3 center;
	vec3 vertexWeights;
	std::vector<Vertex> vertices;

	SurfaceData() : area(0.0), normal(vec3(0.0f)), vertices(std::vector<Vertex>(0, Vertex())){};
	void CalculateSurface(std::vector<Vertex> vertices);
	vec3 CalculateSurfaceAirflow(mat4 trans, vec3* vertices, float area, vec3 normal, vec3 center, vec3 vertexWeights, vec3 linearVel, vec3 angularVel, vec3 windVec);
};