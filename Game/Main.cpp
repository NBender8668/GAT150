#include"pch.h"
#include "Math/Color (2).h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Engine.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"


nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create < nc::GameObject>("ProtoBox");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0,800),nc::random(0,200) };
		gameObject->m_transform.angle = nc::random(0, 360);
		scene.AddGameObject(gameObject);
	}


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

		engine.GetSystem<nc::Renderer>()->BeginFrame();

	
		engine.Update();
		scene.Update();
		
		scene.Draw();


		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}
		
		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}



