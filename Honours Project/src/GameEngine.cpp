#include "GameEngine.h"
#include <assert.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "FileIO.h"

void GameEngine::Initialise()
{
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: glfw failed init! exiting.");
		return;
	}
	FileIO io = FileIO::Get();
	io.LoadIniFile();
	// Create a windowed mode window with hard coded parameters.
	if(fullScreen == false)
		window = glfwCreateWindow(GetScreenWidth(), GetScreenHeight(), "Honours", NULL, NULL);
	else
		window = glfwCreateWindow(GetScreenWidth(),GetScreenHeight(), "Honours", glfwGetPrimaryMonitor(), NULL);
	
	// Window is now initalised, now make it the current context.
	glfwMakeContextCurrent(Get().window);
	if (!Get().window)
	{
		assert(Get().window != NULL);
		CleanUp();
		return;
	}

	// Set up glew.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "ERROR: %p EXITING!", glewGetErrorString(glewInit()));
		return;
	}
	// glExperimental throws junk errors, Ignore.
	glGetError();
	PrintGlewInfo();
	LoadShaders();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// V-Sync, does not run without it
	glfwSwapInterval(1.0f);
}

void GameEngine::Render(glm::mat4 m, Model model, Effect effect)
{
	const auto mvp = Get().cameraMVP * m;
//	Shader::Get().UseShader("Basic", effect, mvp);
	Shader::Get().UseShader("Wind", effect, mvp, m, m, cameraPos, windVector);
	model.Draw();
}

void GameEngine::SetupComputeShader()
{
	glGenBuffers(1, &posSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct pos), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	struct pos *points = (struct pos *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct pos), bufMask);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		points[i].x = i;
		points[i].y = i;
		points[i].z = i;
		points[i].w = 1.;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glGenBuffers(1, &velSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct vel), NULL, GL_STATIC_DRAW);
	struct vel *vels = (struct vel *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct vel), bufMask);

	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		vels[i].vx = i;
		vels[i].vy = i;
		vels[i].vz = i;
		vels[i].vw = 0.;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void GameEngine::SetCamera(glm::mat4 camera)
{
	cameraMVP = camera;
}

void GameEngine::Start()
{
	// Application is over, handle resource cleaning.
	//CleanUp();
}

void GameEngine::CleanUp()
{
	glfwTerminate();

}

void GameEngine::PrintGlewInfo()
{
	printf("-------------------------------------------------------\n");
//	printf("Glew version: %p\n", glewGetString(GLEW_VERSION));

	std::clog << "GL Version: " << glGetString(GL_VERSION) << std::endl;
	std::clog << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::clog << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::clog << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	printf("-------------------------------------------------------\n");
}

void GameEngine::LoadShaders()
{
	Shader::Get().AddShader("Phong");
}