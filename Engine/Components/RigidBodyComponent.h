#pragma once
#include "PhysicsComponents.h"
#include "../Middleware/Box2D/include/box2d/box2d.h"

namespace nc 
{
	class RigidBodyComponent : public PhysicsComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new RigidBodyComponent{ *this }; };


		void Read(const rapidjson::Value& value);
		virtual void Update() override;

		void SetForce(const Vector2& force) override;


	protected:
		PhysicsSystem::RigidBodyData m_data;
		b2Body* m_body{ nullptr };

	};

}