#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

bool nc::SpriteComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	
	return true;
}

void nc::SpriteComponent::Destroy()
{

}

void nc::SpriteComponent::Read(const rapidjson::Value& value)
{
	nc::json::Get(value, "texture", m_textureName);
	nc::json::Get(value, "rect", m_rect);
	nc::json::Get(value, "origin", m_origin);
}

void nc::SpriteComponent::Update()
{

}

void nc::SpriteComponent::Draw()
{
	Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());

	texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, { 1,1 }, m_origin);
}
