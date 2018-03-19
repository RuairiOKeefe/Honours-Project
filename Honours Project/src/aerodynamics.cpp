#include "aerodynamics.h"

void aerodynamics::from_json(const nlohmann::json & j)
{
}

aerodynamics::aerodynamics() :  Component("aerodynamics")
{
}

aerodynamics::aerodynamics(const std::string & fileName) : Component("aerodynamics"), Model(fileName)
{
}

aerodynamics::~aerodynamics()
{
}

void aerodynamics::GenerateSurfaceData() //Should be called after an aerodynamic model is created, only needs to be called once. Parallelisation isn't necessary, if it takes too long to generate consider however
{
	int numverts = vertices.size();
	for (int i = 0; i < numverts/3; i++)
	{
		std::vector<Vertex> polyVerts;
		SurfaceData *tempSurface = new SurfaceData();
		for (int j = 0; j < 3; j++)
		{
			polyVerts.push_back(vertices[i + j]);
		}
		tempSurface->CalculateSurface(polyVerts);
		surfaceData.push_back(*tempSurface);
		polyVerts.clear();
	}
}

void aerodynamics::Update(const double delta)
{
	for (int i = 0; i < surfaceData.size(); i++)
	{
		surfaceData[i].CalculateSurfaceAirflow(vec3(0),0);
	}
}
