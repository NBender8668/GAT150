#include"pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"


nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
int main(int, char**)
{
	renderer.Startup();
	inputSystem.Startup();
	renderer.Create("GAT150",800,600);

	//load texture

	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);

	float angle{ 0 };
	nc::Vector2 position = nc::Vector2 { 400,300 };


	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		//check for event
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		renderer.BeginFrame();

		inputSystem.Update();

		angle = angle + 0.1f;

		
		texture2->Draw(position, { 1,1 }, angle);

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD) 
		{ 
			position.x = position.x - 5.0f; 
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{ 
			position.x = position.x + 5.0f; 
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y - 5.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_DOWN) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y + 5.0f;
		}

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}



