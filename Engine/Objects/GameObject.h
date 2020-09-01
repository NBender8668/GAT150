#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <bitset>
#include <vector>
namespace nc
{
	class Component;
	class Scene;

	class GameObject : public Object
	{
	public:
		enum eFlags
		{
			ACTIVE,
			VISIBLE,
			DESTORY,
			TRANSIENT
		};

	public:

		GameObject() = default;
		GameObject(const GameObject& other);

		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new GameObject{ *this }; };
	

		void Read(const rapidjson::Value& value) override;

		void ReadComponents(const rapidjson::Value& value);

		void Update();
		void Draw();

		void BeginContact(GameObject* gameObject);
		void EndContact(GameObject* gameObject);
		std::vector<GameObject*> GetObjectWithTag(const std::string& tags);

		template<typename T>
		T* GetComponent()
		{
			T* result{ nullptr };
			for (auto component : m_components)
			{
				result = dynamic_cast<T*>(component);
				if (result) break;
			}
			return result;
		}

		void addComponent(Component* component);
		void removeComponent(Component* component);
		void removeAllComponents();

		friend class Component;
		friend class PhysicsComponent;
		
	public:
		std::string m_name;
		std::string m_tag;
		float m_lifetime{ 0 };

		std::bitset<32>m_flags;

		Transform m_transform;
		Engine* m_engine{nullptr};
		Scene* m_scene{ nullptr };

	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;
	};
}