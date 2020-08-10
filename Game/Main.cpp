#include"pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"


nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
nc::FrameTimer timer;


int main(int, char**)
{

	//nc::Timer timer;

	//for (size_t i = 0; i < 100; i++){std::sqrt(rand() % 100);}
	//std::cout << timer.ElapsedSeconds() << std::endl;
	

	renderer.Startup();
	inputSystem.Startup();
	renderer.Create("GAT150",800,600);
	resourceManager.Startup();

	//load texture

	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);
	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);

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

		timer.Tick();
		inputSystem.Update();

		angle = angle + 180 * timer.DeltaTimer();

		
		background->Draw({0,0}, { 1,1 }, 0);
		car->Draw({0,16,64,144}, position, { 1,1 }, 0);

		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD) 
		{ 
			position.x = position.x - 200.0f *timer.DeltaTimer(); 
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{ 
			position.x = position.x + 200.0f * timer.DeltaTimer();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y - 200.0f * timer.DeltaTimer();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_DOWN) == nc::InputSystem::eButtonState::HELD)
		{
			position.y = position.y + 200.0f * timer.DeltaTimer();
		}

		renderer.EndFrame();
	}
	resourceManager.Shutdown();
	inputSystem.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}



