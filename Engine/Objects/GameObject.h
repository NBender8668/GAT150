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
		virtual void Destory() override;

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
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::vector<Component*> m_components;

	};
}