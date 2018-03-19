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
	std::vector<Vertex> vertices;

	SurfaceData() : area(0.0), normal(vec3(0.0f)), vertices(std::vector<Vertex>(0, Vertex())){};
	void CalculateSurface(std::vector<Vertex> vertices);
	vec3 CalculateSurfaceAirflow(vec3 deltaAngle, float deltaTime);
};