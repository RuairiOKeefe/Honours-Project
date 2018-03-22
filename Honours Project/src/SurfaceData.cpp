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

	vertexWeights = vec3(0);
	for (int i = 0; i < 3; i++)
	{
		normal.x = 1;
	}

	center.x = (vertices[0].position.x + vertices[1].position.x + vertices[2].position.x) / 3;
	center.y = (vertices[0].position.y + vertices[1].position.y + vertices[2].position.y) / 3;
	center.z = (vertices[0].position.z + vertices[1].position.z + vertices[2].position.z) / 3;

	vertexWeights.x = distance(vertices[0].position, center);
	vertexWeights.y = distance(vertices[1].position, center);
	vertexWeights.z = distance(vertices[2].position, center);
	vertexWeights = normalize(vertexWeights);
}

vec3 SurfaceData::CalculateSurfaceAirflow(vec3 orientation, float deltaTime)
{
	vec3 faceVel = vec3(0);
	for (int i = 0; i < 3; i++)
	{
		float radius = distance(vertices[i].position, vec3(0));//assuming the center of the model is at (0,0,0)
		vec3 angularVel = radius * (orientation / deltaTime);
		switch (i)
		{
		case(0):
			faceVel += (angularVel*vertexWeights.x);
			return;
		case(1):
			faceVel += (angularVel*vertexWeights.y);
			return;
		case(2):
			faceVel += (angularVel*vertexWeights.z);
			return;
		}
	}

	return vec3();
}
