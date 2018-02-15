#pragma once
#define GLEW_STATIC
#define NUM_PARTICLES 1024*1024 // total number of particles to move
#define WORK_GROUP_SIZE 128 // # work-items per work-group

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <sstream>
#include "Singleton.h"
#include "Material.h"
#include "Model.h"

class Material;


struct pos
{
	float x, y, z, w;// positions
};
struct vel
{
	float vx, vy, vz, vw;  //velocities
};
struct colour
{
	float r, g, b, a; // colours
};

// need to do the following for both position, velocity, and colors of the particles:
GLuint posSSbo;
GLuint velSSbo;
GLuint colSSbo;

struct Effect
{
	unsigned int texture;
	std::string shader;
	Material* material;
};

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
	void SetWindVector(glm::vec3 windVector){ this->windVector = windVector; }
	void SetupComputeShader();

	void SetCamera(glm::mat4 camera);
	// Execute the game engine.
	void Start();
	// Cleans up game engine resources.
	void CleanUp();


	// Helper functions.
	void PrintGlewInfo();
	void LoadShaders();

};