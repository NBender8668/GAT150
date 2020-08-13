#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

bool nc::SpriteComponent::Create(void* data)
{
	m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());

	return true;
}

void nc::SpriteComponent::Destory()
{

}

void nc::SpriteComponent::Update()
{

}

void nc::SpriteComponent::Draw()
{
	m_texture->Draw({ 126, 120, 52, 102 }, m_owner->m_transform.position, { 1,1 }, m_owner->m_transform.angle);
}
