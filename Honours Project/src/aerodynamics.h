#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <string>
#include <vector>
#include <map>
#include "Model.h"
#include "SurfaceData.h"

using namespace glm;
class aerodynamics : public Model, public Component
{
public:
	SurfaceData* surfaceData;

	void from_json(const nlohmann::json & j);

	aerodynamics();
	~aerodynamics();

	void GenerateSurfaceData();
};