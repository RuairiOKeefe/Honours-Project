#include "Game.h"
#include "Entity.h"
#include "Renderable.h"
#include <memory>

int main()
{
	GameEngine::Get().Initialise();

	while (!glfwWindowShouldClose(GameEngine::Get().GetWindow()))
	{
			Game::Get().Update();
			Game::Get().Render();
	}
	GameEngine::Get().CleanUp();
}