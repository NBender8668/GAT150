#include "pch.h"
#include "ContactListener.h"
#include "Objects/GameObject.h"

void nc::ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData())
	{
		GameObject* gameObjectA = static_cast<GameObject*>(fixtureA->GetUserData());
		GameObject* gameObjectB = static_cast<GameObject*>(fixtureB->GetUserData());
	
		gameObjectA->BeginContact(gameObjectB);
		gameObjectB->BeginContact(gameObjectA);
	}

}

void nc::ContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData())
	{
		GameObject* gameObjectA = static_cast<GameObject*>(fixtureA->GetUserData());
		GameObject* gameObjectB = static_cast<GameObject*>(fixtureB->GetUserData());

		gameObjectA->EndContact(gameObjectB);
		gameObjectB->EndContact(gameObjectA);
	}
}
