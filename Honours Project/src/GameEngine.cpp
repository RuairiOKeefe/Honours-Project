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
	if (fullScreen == true)
		window = glfwCreateWindow(GetScreenWidth(), GetScreenHeight(), "Honours", NULL, NULL);
	else
		window = glfwCreateWindow(GetScreenWidth(), GetScreenHeight(), "Honours", glfwGetPrimaryMonitor(), NULL);

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
	Shader::Get().UseShader("Phong", effect, mvp, m, m, cameraPos, windVector);
	model.Draw();
}

void GameEngine::SetupComputeShader()
{
	glGenBuffers(1, &airflowValuesInBuff);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, airflowValuesInBuff);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_OBJECTS * sizeof(struct AirflowValues), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	struct AirflowValues *aValues = (struct AirflowValues *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_OBJECTS * sizeof(struct AirflowValues), bufMask);

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		aValues->trans = glm::mat4(0);
		aValues->vertices[0] = glm::vec3(0);
		aValues->vertices[1] = glm::vec3(0);
		aValues->vertices[2] = glm::vec3(0);
		aValues->area = 0.0;
		aValues->normal = glm::vec3(0);
		aValues->center = glm::vec3(0);
		aValues->vertexWeights = glm::vec3(0);
		aValues->linearVel = glm::vec3(0);
		aValues->angularVel = glm::vec3(0);
		aValues->windVel = glm::vec3(0);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glGenBuffers(1, &forceOutBuff);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, forceOutBuff);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_OBJECTS * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glm::vec3 *force = (glm::vec3 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_OBJECTS * sizeof(glm::vec3), bufMask);

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	std::ifstream ifs("../res/shaders/SimulateSurface.comp");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	const GLchar *source = static_cast<const GLchar *>(content.c_str());

	airflowProgram = glCreateProgram();
	airflowShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(airflowShader, 1, &source, NULL);
	glCompileShader(airflowShader);
	glAttachShader(airflowProgram, airflowShader);
	glLinkProgram(airflowProgram);
}

glm::vec3* GameEngine::InvokeComputeShader(mat4 trans, std::vector<SurfaceData> surfaceData, vec3 linearVel, vec3 angularVel, vec3 windVec)
{

	glGenBuffers(1, &airflowValuesInBuff);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, airflowValuesInBuff);
	glBufferData(GL_SHADER_STORAGE_BUFFER, surfaceData.size() * sizeof(struct AirflowValues), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	struct AirflowValues *aValues = (struct AirflowValues *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, surfaceData.size() * sizeof(struct AirflowValues), bufMask);

	for (int i = 0; i < surfaceData.size(); i++)
	{
		aValues->trans = trans;
		aValues->vertices[0] = surfaceData[i].vertices[0].position;
		aValues->vertices[1] = surfaceData[i].vertices[1].position;
		aValues->vertices[2] = surfaceData[i].vertices[2].position;
		aValues->area = surfaceData[i].area;
		aValues->normal = surfaceData[i].normal;
		aValues->center = surfaceData[i].center;
		aValues->vertexWeights = surfaceData[i].vertexWeights;
		aValues->linearVel = linearVel;
		aValues->angularVel = angularVel;
		aValues->windVel = windVec;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glGenBuffers(1, &forceOutBuff);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, forceOutBuff);
	glBufferData(GL_SHADER_STORAGE_BUFFER, surfaceData.size() * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glm::vec3 *force = (glm::vec3 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, surfaceData.size() * sizeof(glm::vec3), bufMask);

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, airflowValuesInBuff);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, forceOutBuff);

	glUseProgram(airflowProgram);
	glDispatchCompute(surfaceData.size() / WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	return force;
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