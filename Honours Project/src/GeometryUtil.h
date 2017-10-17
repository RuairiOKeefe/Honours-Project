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

		Model* temp  = new Model(vertices,indices);
		temp->SetType(GL_TRIANGLE_STRIP);
		return temp;
	}

	static Model* BuildCube(float size)
	{

		int indices[] =
		{
			7,6,3,2,0,
			6,4,7,5,
			3,1,0,5,4

			//0, 1, 2, 3, 8, // Front wall
			//4, 5, 6, 7, 8, // Back wall
			//4, 0, 6, 3, 8, // Left wall
			//1, 5, 3, 7, 8, // Right wall
			//2, 3, 6, 7, 8, // Top wall
			//0, 1, 4, 5  // Bottom wall
		};

		glm::vec3 lowerLeftFront = glm::vec3(size, size, -size),
			upperRightBack = glm::vec3(-size, -size, size);

		glm::vec3 vertices[] =
		{
			// Front wall of bounding box
			lowerLeftFront,
			glm::vec3(upperRightBack.x, lowerLeftFront.y, lowerLeftFront.z),
			glm::vec3(lowerLeftFront.x, upperRightBack.y, lowerLeftFront.z),
			glm::vec3(upperRightBack.x, upperRightBack.y, lowerLeftFront.z),
			// Back wall of bounding box
			glm::vec3(lowerLeftFront.x, lowerLeftFront.y, upperRightBack.z),
			glm::vec3(upperRightBack.x, lowerLeftFront.y, upperRightBack.z),
			glm::vec3(lowerLeftFront.x, upperRightBack.y, upperRightBack.z),
			upperRightBack
		};

		Model* temp = new Model(vertices, indices);
		temp->SetType(GL_TRIANGLES);
		return temp;
	}

	static Model BuildLine()
	{
		std::cout << "Not Implemented!" << std::endl;
	}

};