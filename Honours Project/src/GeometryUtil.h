#pragma once
#include "Model.h"
#include <iostream>
#include <glm\common.hpp>
#include <vector>
static class GeometryUtil
{
public:
	static Model* BuildPlane(float spacing, unsigned int xSize, unsigned int ySize)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for (int i = 0; i < ySize; i++)
		{
			for (int j = 0; j < xSize; j++)
			{
				Vertex v;
				v.position = glm::vec3(j*spacing, 0.0f, i*spacing);
				v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
				v.texCoords = glm::vec2(j*spacing, i*spacing);
				v.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
				vertices.push_back(v);
			}
		}
		for (int i = 0; i < ySize - 1; i++)
		{
			if ((i & 1) == 0)
			{ // even rows
				for (int j = 0; j < xSize; j++)
				{
					indices.push_back(j + (i*xSize));
					indices.push_back(j + ((i + 1) * xSize));
				}
			}
			else
			{ // odd rows
				for (int j = xSize - 1; j > 0; j--)
				{
					indices.push_back(j + ((i + 1) * xSize));
					indices.push_back(j - 1 + (i * xSize));
				}
			}
		}

		Model* temp = new Model(vertices, indices);
		temp->SetType(GL_TRIANGLE_STRIP);
		return temp;
	}

	static Model* BuildCube(float size)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices
		{
			0,3,2, 2,1,0,
			3,0,4, 4,0,7,
			0,1,6, 6,7,0,
			7,6,5, 5,4,7,
			4,5,2, 2,3,4,
			6,1,5, 5,1,2
		};

		glm::vec3 upperLeftFront = glm::vec3(size, size, size),
			lowerRightBack = glm::vec3(-size, -size, -size);

		Vertex v;
		// Front wall of bounding box
		v.position = upperLeftFront;
		v.normal = upperLeftFront;
		vertices.push_back(v);

		v.position = glm::vec3(upperLeftFront.x, lowerRightBack.y, upperLeftFront.z);
		v.normal = glm::vec3(upperLeftFront.x, lowerRightBack.y, upperLeftFront.z);
		vertices.push_back(v);

		v.position = glm::vec3(upperLeftFront.x, lowerRightBack.y, lowerRightBack.z);
		v.normal = glm::vec3(upperLeftFront.x, lowerRightBack.y, lowerRightBack.z);
		vertices.push_back(v);

		v.position = glm::vec3(upperLeftFront.x, upperLeftFront.y, lowerRightBack.z);
		v.normal = glm::vec3(upperLeftFront.x, upperLeftFront.y, lowerRightBack.z);
		vertices.push_back(v);

		v.position = glm::vec3(lowerRightBack.x, upperLeftFront.y, lowerRightBack.z);
		v.normal = glm::vec3(lowerRightBack.x, upperLeftFront.y, lowerRightBack.z);
		vertices.push_back(v);

		v.position = lowerRightBack;
		v.normal = lowerRightBack;
		vertices.push_back(v);

		v.position = glm::vec3(lowerRightBack.x, lowerRightBack.y, upperLeftFront.z);
		v.normal = glm::vec3(lowerRightBack.x, lowerRightBack.y, upperLeftFront.z);
		vertices.push_back(v);

		v.position = glm::vec3(lowerRightBack.x, upperLeftFront.y, upperLeftFront.z);
		v.normal = glm::vec3(lowerRightBack.x, upperLeftFront.y, upperLeftFront.z);
		vertices.push_back(v);

		Model* temp = new Model(vertices, indices);
		temp->SetType(GL_TRIANGLES);
		return temp;
	}

	static Model BuildLine()
	{
		std::cout << "Not Implemented!" << std::endl;
	}

};