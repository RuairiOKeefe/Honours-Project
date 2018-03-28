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
	std::vector<SurfaceData> surfaceData;

	void from_json(const nlohmann::json & j);

	aerodynamics();
	aerodynamics(const std::string& fileName);
	~aerodynamics();

	void GenerateSurfaceData();
	void Update(const double delta);
};