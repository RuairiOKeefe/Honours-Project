#pragma once
#define GLEW_STATIC
#define GLFW_DLL
#define NUM_OBJECTS 512*512
#define WORK_GROUP_SIZE 128 // # work-items per work-group

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <sstream>
#include "Singleton.h"
#include "Material.h"
#include "Model.h"
#include "SurfaceData.h"

class Material;


struct AirflowValues
{
	glm::mat4 trans;
	glm::vec3 vertices[3];
	float area;
	glm::vec3 normal, center, vertexWeights, linearVel, angularVel, windVel;
};

struct Effect
{
	unsigned int texture;
	std::string shader;
	Material* material;
};

using namespace glm;

class GameEngine : public Singleton<GameEngine>
{
private:

	// The window that is to be rendered too.
	GLFWwindow* window;
	float width;
	float height;
	bool fullScreen;
	glm::mat4 cameraMVP;
	glm::vec3 cameraPos;
	glm::vec3 windVector;

	GLuint airflowShader;
	GLuint airflowProgram;
	GLuint airflowValuesInBuff;
	GLuint forceOutBuff;

public:

	// The render window.
	GLFWwindow* GetWindow() { return window; }

	void Initialise();
	void Render(glm::mat4 mvp, Model model, Effect effect);

	// Getters for width and height
	float GetScreenWidth() { return width; }
	float GetScreenHeight() { return height; }
	bool GetFullScreen() { return fullScreen; }
	void SetFullScreen(int val) { fullScreen = val; }
	void SetScreenWidth(int val) { width = val; }
	void SetScreenHeight(int val) { height = val; }
	void SetCameraPos(glm::vec3 pos) { cameraPos = pos; }
	void SetWindVector(glm::vec3 windVector) { this->windVector = windVector; }

	void SetupComputeShader();
	glm::vec3* InvokeComputeShader(mat4 trans, std::vector<SurfaceData> surfaceData, vec3 linearVel, vec3 angularVel, vec3 windVec);

	void SetCamera(glm::mat4 camera);
	// Execute the game engine.
	void Start();
	// Cleans up game engine resources.
	void CleanUp();


	// Helper functions.
	void PrintGlewInfo();
	void LoadShaders();

};