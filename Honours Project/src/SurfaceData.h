#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <string>
#include <vector>
#include <map>
#include "Model.h"

using namespace glm;
class SurfaceData : public Component
{
	double area;
	vec3 normal;

	void CalculateSurface(Vertex* vertices);
	vec3 CalculateSurfaceAirflow(Vertex* vertices, vec3 deltaAngle, float deltaTime);
};