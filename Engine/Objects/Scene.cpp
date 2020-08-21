#include "pch.h"
#include "Scene.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "ObjectFactory.h"
#include "GameObject.h"


bool nc::Scene::Create(void* data)
{
	m_engine = static_cast<Engine*>(data);

	return true;
}

void nc::Scene::Destroy()
{
	RemoveAllGameObjects();
}

void nc::Scene::Read(const rapidjson::Value& value)
{
	//const rapidjson::Value& objectValue = value["GameObject"];
	//if (objectValue.IsObject())
	//{
	//	std::string typeName;
	//	// read component “type” name from json (Get)

	//	nc::json::Get(objectValue, "type", typeName);

	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(typeName);
	//	

	//		if (gameObject)
	//		{
	//			gameObject->Create(m_engine);
	//			// call game object read (pass in objectValue)
	//			gameObject->Read(objectValue);

	//			// call AddGameObject passing in the game object
	//			AddGameObject(gameObject);
	//		}


	//}
			const rapidjson::Value& objectsValue = value["GameObjects"];
			if (objectsValue.IsArray())
			{
				ReadGameObjects(objectsValue);
			}

}

void nc::Scene::Update()
{
	for (auto gameObject : m_gameObjects)
	{
		gameObject->Update();
	}
}

void nc::Scene::Draw()
{
	for (auto gameObject : m_gameObjects)
	{
		gameObject->Draw();
	}
}

void nc::Scene::ReadGameObjects(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++)
	{
		const rapidjson::Value& objectValue = value[i];
		if (objectValue.IsObject())
		{
			std::string typeName;
			// read game object “type” name from json (Get)
			nc::json::Get(objectValue, "type", typeName);

			GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>(typeName);

				if (gameObject)
				{

					gameObject->Create(m_engine);
				
					gameObject->Read(objectValue);

					
					AddGameObject(gameObject);

					// call game object create, pass in m_engine
					// call game object read
					// add game object to scene
				}
		}
	}

}

nc::GameObject* nc::Scene::Find(const std::string& name)
{
	for (auto gameObject : m_gameObjects)
	{
		// compare game object name to name parameter (==)
		if(gameObject->m_name == name)
		{ 
		
			return gameObject;
		}
	}
	return nullptr;

}

void nc::Scene::AddGameObject(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);
}

void nc::Scene::RemoveGameObject(GameObject* gameObject)
{
	auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (iter != m_gameObjects.end())
	{
		// destroy (*iter)->
		(*iter)->Destroy();

		// delete 
		delete* iter;

		// erase iter from m_gameObjects
		m_gameObjects.erase(iter);
	}

}

void nc::Scene::RemoveAllGameObjects()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		// destroy
		gameObject->Destroy();
		// delete
		delete(gameObject);
	}

	// clear game objects
	m_gameObjects.clear();
}
