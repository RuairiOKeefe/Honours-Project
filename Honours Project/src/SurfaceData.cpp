#include "SurfaceData.h"

void SurfaceData::CalculateSurface(Vertex* Vertices)
{
	glm::vec3 AB, AC;
	float angle;
	AB = Vertices[0].position - Vertices[1].position;
	AC = Vertices[0].position - Vertices[2].position;
	angle = (glm::dot(AB, AC)) / (glm::length(AB) * glm::length(AC));

	area = 0.5 * (glm::length(AB) * glm::length(AC)) * sin(angle);

	normal = glm::vec3(0, 0, 0);

	for (int i = 0; i < 3; i++)
	{
		normal.x = 1;
	}
}
