#include "SurfaceData.h"

void SurfaceData::CalculateSurface(std::vector<Vertex> vertices)
{
	this->vertices = vertices;
	vec3 AB, AC;
	float angle;
	AB = vertices[0].position - vertices[1].position;
	AC = vertices[0].position - vertices[2].position;
	angle = (dot(AB, AC)) / (length(AB) * length(AC));

	area = 0.5 * (length(AB) * length(AC)) * sin(angle);

	normal = vec3(0, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		normal.x = 1;
	}
}

vec3 SurfaceData::CalculateSurfaceAirflow(vec3 deltaAngle, float deltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		float radius = distance(vertices[i].position, vec3(0));//fill in with model centerpoint, which we will need to gather
		vec3 angularVel = radius * (deltaAngle/deltaTime);
	}

	return vec3();
}
