#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "Graphics/Texture.h"

bool nc::SpriteAnimationComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);

	return true;
}

void nc::SpriteAnimationComponent::Destroy()
{

}

void nc::SpriteAnimationComponent::Read(const rapidjson::Value& value)
{
	SpriteComponent::Read(value);

	json::Get(value, "numX", m_numX);
	json::Get(value, "numY", m_numY);
	json::Get(value, "numFrames", m_numframes);
	json::Get(value, "fps", m_fps);

	m_framerate = 1.0f / m_fps;
}

void nc::SpriteAnimationComponent::Update()
{

	m_frame_Timer += m_owner->m_engine->GetTimer().DeltaTimer();

	if (m_frame_Timer >= m_framerate)
	{
		m_frame_Timer = 0;
		m_frame++;
		if (m_frame >= m_numframes) m_frame = 0;
	}

	//update frame rect
	Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
	Vector2 textureSize = texture->GetSize();
	Vector2 cellSize = textureSize / Vector2{ m_numX, m_numY };

	m_rect.x = static_cast<int>((m_frame % m_numX) * cellSize.x);
	m_rect.y = static_cast<int>((m_frame / m_numX) * cellSize.y);
	m_rect.w = static_cast<int>(cellSize.x);
	m_rect.h = static_cast<int> (cellSize.y);
}
