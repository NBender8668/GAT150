#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <vector>
namespace nc
{
	class Component;

	class GameObject : public Object
	{
	public:

		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		void Read(const rapidjson::Value& value) override;

		void ReadComponents(const rapidjson::Value& value);

		void Update();
		void Draw();

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
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::vector<Component*> m_components;

	};
}