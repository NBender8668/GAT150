#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"

namespace nc
{
	bool GameObject::Create(void* data )
	{
		m_engine = static_cast<Engine*>(data);

		return true;
	}

	void GameObject::Destory()
	{
		removeAllComponents();
	}

	void GameObject::Update()
	{
		for (auto component : m_components)
		{
			component->Update();
		}
	}

	void GameObject::Draw()
	{
	
		RenderComponent* component = GetComponent<RenderComponent>();
		if (component)
		{
			component->Draw();
		}
		
	}

	void GameObject::addComponent(Component* component)
	{
		component->m_owner = this;

		m_components.push_back(component);
	}

	void GameObject::removeComponent(Component* component)
	{
		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end())
		{
			(*iter)->Destory();
			delete(*iter);
		}
	}

	void GameObject::removeAllComponents()
	{
		for (auto component : m_components)
		{
			component->Destory();
			delete component;
		}
		m_components.clear();
	}
}
