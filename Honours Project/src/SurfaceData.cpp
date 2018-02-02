#include "SurfaceData.h"

void SurfaceData::CalculateSurface(Vertex* Vertices)
{
	vec3 AB, AC;
	float angle;
	AB = Vertices[0].position - Vertices[1].position;
	AC = Vertices[0].position - Vertices[2].position;
	angle = (dot(AB, AC)) / (length(AB) * length(AC));

	area = 0.5 * (length(AB) * length(AC)) * sin(angle);

	normal = vec3(0, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		normal.x = 1;
	}
}

vec3 SurfaceData::CalculateSurfaceAirflow(Vertex * vertices)
{
	for (int i = 0; i < 3; i++)
	{
		float radius = distance(vertices[i].position, vec3(0));//fill in with model centerpoint, which we will need to gather
		//angular momentum = radius * (deltaAngle/deltaTime);
	}

	return vec3();
}
