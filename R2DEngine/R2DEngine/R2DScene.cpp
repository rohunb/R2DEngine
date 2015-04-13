#include "R2DScene.h"
#include <algorithm>
#include "GameObject.h"
#include "RDebug.h"
#include "TextureManager.h"
#include "RenderEngine.h"
#include "R2DScript.h"

using namespace rb;

rb::R2DScene::R2DScene()
{}

rb::R2DScene::R2DScene(const R2DScene& rhs)
	:sceneObjects(rhs.sceneObjects),
	OnInstantiate(rhs.OnInstantiate),
	OnDestroy(rhs.OnDestroy)
{}
R2DScene& rb::R2DScene::operator=(const R2DScene& rhs)
{
	sceneObjects = rhs.sceneObjects;
	OnInstantiate = OnInstantiate;
	OnDestroy = rhs.OnDestroy;
	return *this;
}
rb::R2DScene::R2DScene(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	OnInstantiate = std::move(rhs.OnInstantiate);
	OnDestroy = std::move(rhs.OnDestroy);
}
R2DScene& rb::R2DScene::operator=(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	OnInstantiate = std::move(rhs.OnInstantiate);
	OnDestroy = std::move(rhs.OnDestroy);
	return *this;
}

rb::Colour rb::R2DScene::BackgroundColour() const
{
	return backgroundColour;
}

void rb::R2DScene::SetupCallbacks(std::function<void(GameObject&)> OnInstantiate, std::function<void(std::shared_ptr<GameObject>&)> OnDestroy)
{
	assert(OnInstantiate);
	assert(OnDestroy);
	this->OnInstantiate = OnInstantiate;
	this->OnDestroy = OnDestroy;
}

void rb::R2DScene::DestroyAllObjects()
{
	Debug::Log("Destroying all scene objs");
	while (!sceneObjects.empty())
	{
		Destroy(sceneObjects[0]);
	}
	sceneObjects.clear();
}
void rb::R2DScene::RemoveDestroyedObjects()
{
	int i = sceneObjects.size() - 1;
	while (i >= 0 )
	{
		if (sceneObjects[i]->destroyed)
		{
			Destroy(sceneObjects[i]);
		}
		else
		{
			--i;
		}
	}
}

void rb::R2DScene::SetBackgroundColour(const Colour& val)
{
	backgroundColour = val;
	RenderEngine::SetClearColour(backgroundColour);
}

std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab)
{
	return Instantiate(prefab, prefab.GetTransform()->position, prefab.GetTransform()->rotation);
}

std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(std::move(prefab));
	objClone->SetTransform(position, rotation);
	sceneObjects.push_back(objClone);
	assert(OnInstantiate && "Instantiate callback is null");
	OnInstantiate(*objClone);
	return objClone;
}
void rb::R2DScene::Destroy(std::shared_ptr<GameObject>& gameObject)
{
	assert(std::find(sceneObjects.begin(), sceneObjects.end(), gameObject) != sceneObjects.end() && "GameObject is not present in the scene");
	assert(OnDestroy && "OnDestroy is null");
	OnDestroy(gameObject);
	assert(std::find(sceneObjects.begin(), sceneObjects.end(), gameObject) != sceneObjects.end() && "GameObject is not present in the scene");
	sceneObjects.erase(std::remove(sceneObjects.begin(), sceneObjects.end(), gameObject), sceneObjects.end());
	
	//Debug::Log("After destruction: Gameobject refs: " + ToString(gameObject.use_count()) +
	//	" trans: " + ToString(gameObject->GetTransform().use_count()) +
	//	" rigidbody: " + ToString(gameObject->GetRigidbody().use_count()) +
	//	" renderer: " + ToString(gameObject->GetRenderer().use_count()));
}

void rb::R2DScene::Update(float dt)
{
	//Debug::Log("scene Update");
	size_t numSceneObjs = sceneObjects.size();
	for (size_t i = 0; i < numSceneObjs; i++)
	{
		size_t numScripts = sceneObjects[i]->GetScripts().size();
		for (size_t j = 0; j < numScripts; j++)
		{
			sceneObjects[i]->GetScripts()[j]->Update(dt);
		}
	}
}

