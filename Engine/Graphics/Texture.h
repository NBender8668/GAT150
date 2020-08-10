#pragma once
#include"Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL.h>
#include <string>

namespace nc
{
	class Texture : public Resource
	{
	public:
		virtual bool Create(const std::string name, void* data = nullptr) override;

		void Destory() override;

		void Draw(const Vector2& position, const Vector2& scale, float angle);
		void Draw(const SDL_Rect& source ,const Vector2& position, const Vector2& scale, float angle);

		Vector2 GetSize();

	protected:

		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };

		
	};
}