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
	if (value.HasMember("Prototypes"))
	{
		const rapidjson::Value& objectsValue = value["Prototypes"];
		if (objectsValue.IsArray())
		{
			ReadPrototypes(objectsValue);
		}

	}

	if (value.HasMember("GameObjects"))
	{
		const rapidjson::Value& objectsValue = value["GameObjects"];
		if (objectsValue.IsArray())
		{
			ReadGameObjects(objectsValue);
		}


	}
		
}

void nc::Scene::ReadPrototypes(const rapidjson::Value& value)
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

				gameObject->Create(this);

				gameObject->Read(objectValue);

				std::cout << gameObject->m_name << std::endl;


				ObjectFactory::Instance().Register(gameObject->m_name, new Prototype<Object>(gameObject));

				
			}
		}
	}
}

void nc::Scene::Update()
{
	for (auto gameObject : m_gameObjects)
	{
		gameObject->Update();
	}

	auto iter = m_gameObjects.begin();
	while (iter != m_gameObjects.end())
	{
		if ((*iter)->m_flags[GameObject::eFlags::DESTORY])
		{
			(*iter)->Destroy();
			delete(*iter);
			iter = m_gameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
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

					gameObject->Create(this);
				
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

std::vector<nc::GameObject*> nc::Scene::FindGameObjectsWithTag(const std::string& tag)
{
	 std::vector<GameObject*> gameobjects;

	 for (auto gameObject : m_gameObjects)
	 {
		 // compare game object name to name parameter (==)
		 if (gameObject->m_tag == tag)
		 {

			gameobjects.push_back(gameObject);
		 }
	 }

	 return gameobjects;
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
