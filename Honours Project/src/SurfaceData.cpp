#include "SurfaceData.h"
#include "Game.h"
#define AIR_PRESSURE 1.2041f //Air Pressure at 1 atm at 20C

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

	normal = cross(AB, AC);
	normal = normalize(normal);//Check for a use for this

	center.x = (vertices[0].position.x + vertices[1].position.x + vertices[2].position.x) / 3;
	center.y = (vertices[0].position.y + vertices[1].position.y + vertices[2].position.y) / 3;
	center.z = (vertices[0].position.z + vertices[1].position.z + vertices[2].position.z) / 3;

	vertexWeights.x = distance(vertices[0].position, center);
	vertexWeights.y = distance(vertices[1].position, center);
	vertexWeights.z = distance(vertices[2].position, center);
	vertexWeights = normalize(vertexWeights);
}

vec3 SurfaceData::CalculateSurfaceAirflow(mat4 trans, vec3* vertices, float area, vec3 normal, vec3 center, vec3 vertexWeights, vec3 linearVel, vec3 angularVel, vec3 windVec)
{
	vec3 faceVel = vec3(0);
	normal = vec4(normal, 0) * transpose(inverse(trans));
	for (int i = 0; i < 3; i++)
	{
		vertices[i] = vec4(vertices[i], 0) * transpose(trans);

		float radius = distance(vertices[i], vec3(0));//assuming the center of the model is at (0,0,0)
		vec3 localVel = linearVel + cross(angularVel, vertices[i]);
		switch (i)
		{
		case(0):
			faceVel += (localVel*vertexWeights.x);
			break;
		case(1):
			faceVel += (localVel*vertexWeights.y);
			break;
		case(2):
			faceVel += (localVel*vertexWeights.z);
			break;
		}
	}

	vec3 relativeVel = faceVel + windVec;
	vec3 finalVel = normal * max(dot(relativeVel, normal), 0.0f);
	vec3 force = (0.5f*(AIR_PRESSURE)*(finalVel*finalVel)*area);
	force = length(force) * -normal;

	if (glm::isnan(force.x))
		return vec3(0);

	return vec3(force);
}
