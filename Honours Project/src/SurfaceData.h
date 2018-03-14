#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <string>
#include <vector>
#include <map>
#include "Model.h"

using namespace glm;
class SurfaceData
{
public:
	double area;
	vec3 normal;

	void CalculateSurface(std::vector<Vertex> vertices);
	vec3 CalculateSurfaceAirflow(std::vector<Vertex> vertices, vec3 deltaAngle, float deltaTime);
};