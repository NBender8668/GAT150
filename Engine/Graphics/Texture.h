#pragma once
#include"Math/Vector2.h"
#include <SDL.h>
#include <string>
namespace nc
{
	class Texture
	{
	public:
		bool Create(const std::string& name, SDL_Renderer* renderer);

		void Destory();

		void Draw(const Vector2& position, const Vector2& scale, float angle);

		Vector2 GetSize();

	protected:

		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}