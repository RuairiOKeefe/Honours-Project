#include "aerodynamics.h"

void aerodynamics::from_json(const nlohmann::json & j)
{
}

aerodynamics::aerodynamics() : Component("aerodynamics")
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
		for (int j = 0; j < 3; j++)
		{
			polyVerts.push_back(vertices[i + j]);
		}
		surfaceData[i].CalculateSurface(polyVerts);
		polyVerts.clear();
	}
}