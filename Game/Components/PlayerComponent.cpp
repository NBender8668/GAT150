#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponents.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);

	return true;
}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	

	nc::Vector2 force{ 0,0 };
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -200000;
		//m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTimer();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 200000;
		//m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTimer();
	}

	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -400000;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		if (audioComponent)
		{
			audioComponent->Play();
		}

		
	}



	//if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
	//{
	//	force = nc::Vector2::forward * 1000.0f;
	//}
	//force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->SetForce(force);
	}
}
