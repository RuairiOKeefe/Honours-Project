#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <string>
#include <vector>
#include <map>
#include "Model.h"

class SurfaceData
{
	double area;
	glm::vec3 normal;

	void CalculateSurface(Vertex* vertices);
};