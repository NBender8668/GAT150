#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"

b2Body* nc::PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
{
	b2BodyDef bodyDef;  

	bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;        
	bodyDef.position.Set(position.x, position.y);        
	b2Body* body = m_world->CreateBody(&bodyDef);   

	b2PolygonShape shape;        
	shape.SetAsBox(size.x, size.y);        
	body->CreateFixture(&shape, density);        
	return body;
}

b2Body* nc::PhysicsSystem::CreateBody(const Vector2& position, const RigidBodyData& data, GameObject* gameObject)
{
	b2BodyDef bodyDef;

	bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = data.lockAngle;
	b2Body* body = m_world->CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	
	shape.SetAsBox(data.size.x, data.size.y);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = data.density;
	fixtureDef.friction = data.friction;
	fixtureDef.restitution = data.restitution;
	fixtureDef.userData = gameObject;

	body->CreateFixture(&fixtureDef);

	return body;
}

bool nc::PhysicsSystem::Startup()
{
	b2Vec2 gravity(0, 150);
	
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