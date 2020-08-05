#include"pch.h"
#include "Graphics/Texture.h"

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//create textures
	int width = 128;
	int height = 128;

	SDL_Texture* texture1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];
	memset(pixels, 128, width * height * sizeof(Uint32));
	SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));

	//load texture
	nc::Texture texture;
	texture.Create("sf2.png", renderer);
	float angle{ 0 };

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


		SDL_SetRenderDrawColor(renderer, 0, 0, 134, 255);
		
		//clear frame buffer
		SDL_RenderClear(renderer);

		//draw
		for (size_t i = 0; i < width * height; i++)
		{
			Uint8 c = rand() % 256;
			pixels[i] = (c << 24 | c << 16 | c << 8);
		}

		//pixel memory = (8/8/8/8), (8/8/8/8)

		SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(Uint32));
		SDL_Rect rect;
		rect.x = 200;
		rect.y = 200;
		rect.w = width;
		rect.h = height;
		SDL_RenderCopy(renderer, texture1, NULL, &rect );

		angle = angle + 0.1f;
		texture.Draw({ 500,100 }, { 2.0f,2.0f }, angle);


		//present/show render
		SDL_RenderPresent(renderer);

	}

	IMG_Quit();
	SDL_Quit();

	return 0;
}



