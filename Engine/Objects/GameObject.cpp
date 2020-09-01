#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "Scene.h"
#include "ObjectFactory.h"

namespace nc
{
	GameObject::GameObject(const GameObject& other)
	{
		m_name = other.m_name;
		m_tag = other.m_tag;
		m_lifetime = other.m_lifetime;

		m_flags = other.m_flags;

		m_transform = other.m_transform;
		m_engine = other.m_engine;
		m_scene = other.m_scene;

		for (Component* component : other.m_components)
		{
			Component* clone = dynamic_cast<Component*>(component->Clone());
			clone->m_owner = this;
			addComponent(clone);
		}
	}

	bool GameObject::Create(void* data )
	{
		m_scene = static_cast<Scene*>(data);
		m_engine = m_scene->m_engine;

		return true;
	}

	void GameObject::Destroy()
	{
		removeAllComponents();
	}

	void GameObject::Read(const rapidjson::Value& value)
	{
		nc::json::Get(value, "name", m_name);
		nc::json::Get(value, "tag", m_tag);
		nc::json::Get(value, "lifetime", m_lifetime);

		bool transient = m_flags[eFlags::TRANSIENT];
		nc::json::Get(value, "transient", transient);
		m_flags[eFlags::TRANSIENT] = transient;

		nc::json::Get(value, "position", m_transform.position);
		nc::json::Get(value, "scale", m_transform.scale);
		nc::json::Get(value, "angle", m_transform.angle);

		if (value.HasMember("Components"))
		{
			const rapidjson::Value& componentsValue = value["Components"];
			if (componentsValue.IsArray())
			{
				ReadComponents(componentsValue);
			}

		}


	}

	void GameObject::ReadComponents(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& componentValue = value[i];
			if (componentValue.IsObject())
			{
				std::string typeName;
				// read component “type” name from json (Get)
				nc::json::Get(componentValue, "type", typeName);

				Component* component = nc::ObjectFactory::Instance().Create<nc::Component>(typeName);
					if (component)
					{
						// call component create, pass in gameobject (this)
						component->Create(this);
						// call component read
						component->Read(componentValue);
						// add component to game object
						GameObject::addComponent(component);
					}
			}
		}

	}

	void GameObject::Update()
	{
		for (auto component : m_components)
		{
			component->Update();
		}

		if (m_flags[eFlags::TRANSIENT])
		{
			m_lifetime = m_lifetime - m_engine->GetTimer().DeltaTimer();
			m_flags[eFlags::DESTORY] = (m_lifetime <= 0);
			
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

	void GameObject::BeginContact(GameObject* gameObject)
	{
		m_contacts.push_back(gameObject);

		Event event;
		event.type = "CollisionEnter";
		event.sender = gameObject;
		event.receiver = this;

		EventManager::Instance().Notify(event);
	}

	void GameObject::EndContact(GameObject* gameObject)
	{
		m_contacts.remove(gameObject);

		Event event;
		event.type = "CollisionExit";
		event.sender = gameObject;
		event.receiver = this;

		EventManager::Instance().Notify(event);
	}

	std::vector<GameObject*> GameObject::GetObjectWithTag(const std::string& tags)
	{
		std::vector<GameObject*> contacts;

		for (auto contact : m_contacts)
		{
			if (contact->m_tag == tags)
			{
				contacts.push_back(contact);
			}
		}

		return contacts;
	}

	void GameObject::addComponent(Component* component)
	{
		m_components.push_back(component);
	}

	void GameObject::removeComponent(Component* component)
	{
		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end())
		{
			(*iter)->Destroy();
			delete(*iter);
		}
	}

	void GameObject::removeAllComponents()
	{
		for (auto component : m_components)
		{
			component->Destroy();
			delete component;
		}
		m_components.clear();
	}
}
