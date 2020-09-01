#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"



b2Body* nc::PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameObject)
{
	b2BodyDef bodyDef;

	Vector2 world = PhysicsSystem::ScreenToWorld(position);

	bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(world.x, world.y);
	bodyDef.angle = DegreesToRadians(angle);
	bodyDef.fixedRotation = data.lockAngle;
	b2Body* body = m_world->CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	Vector2 worldsize = PhysicsSystem::ScreenToWorld(data.size);
	shape.SetAsBox(worldsize.x, worldsize.y);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = data.density;
	fixtureDef.friction = data.friction;
	fixtureDef.restitution = data.restitution;
	fixtureDef.isSensor = data.isSensor;
	fixtureDef.userData = gameObject;

	body->CreateFixture(&fixtureDef);

	return body;
}

void nc::PhysicsSystem::DestoryBody(b2Body* body)
{
	m_world->DestroyBody(body);
}

bool nc::PhysicsSystem::Startup()
{
	b2Vec2 gravity(0, 20);
	
	m_world = new b2World{ gravity };

	m_contactListenr = new ContactListener;
	m_world->SetContactListener(m_contactListenr);

	return true;
}

void nc::PhysicsSystem::Shutdown()
{
	delete(m_world);
	m_world = nullptr;
}

void nc::PhysicsSystem::Update()
{
	float timestep = 1.0 / 60.0;
	m_world->Step(timestep, 8, 3);
}
