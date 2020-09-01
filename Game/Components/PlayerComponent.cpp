#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponents.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/EventManager.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);

	EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
	EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);

	return true;
}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	auto contacts = m_owner->GetObjectWithTag("floor");
	bool onground = !contacts.empty();

	nc::Vector2 force{ 0,0 };
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -150;
		//m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTimer();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 150;
		//m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTimer();
	}

	if (onground && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -1500;

	/*	AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		if (audioComponent)
		{
			//audioComponent->SetSoundName("audio/jump.wav")
			audioComponent->Play();
		}*/

	}

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->ApplyForce(force);

		Vector2 velocity = component->GetVelocity();

		SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
		if (velocity.x <= -0.5f) spriteComponent->Flip();
		if (velocity.x >= 0.5f) spriteComponent->Flip(false);
	};


}
void nc::PlayerComponent::OnCollisionEnter(const Event& event)
{
	GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

	//std::cout << "collision Enter: "<< gameObject->m_name << std::endl;

	if (gameObject->m_tag == "enemy")
	{
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();

		audioComponent->SetSoundName("audio/Grunt.wav");
		audioComponent->Play();

		gameObject->m_flags[GameObject::eFlags::DESTORY] = true;

	}

	if (gameObject->m_tag == "coin")
	{

		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
					
		audioComponent->SetSoundName("audio/jump.wav");
		audioComponent->Play();

		gameObject->m_flags[GameObject::eFlags::DESTORY] = true;
							
	}
	
}

void nc::PlayerComponent::OnCollisionExit(const Event& event)
{

	GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

	//std::cout << "collision Exit: " << gameObject->m_name << std::endl;
}

