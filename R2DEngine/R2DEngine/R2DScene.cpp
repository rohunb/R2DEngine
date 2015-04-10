#include "R2DScene.h"
#include "GameObject.h"
#include "RDebug.h"
#include "TextureManager.h"

using namespace rb;

rb::R2DScene::R2DScene(std::function<void(GameObject&)> _instantiateCallback)
	//:instantiateCallback(_instantiateCallback)
{
	Debug::Log("Scene ctor");
	this->instantiateCallback = _instantiateCallback;
	/*missile = std::make_shared<GameObject>(TextureManager::GetTexture("Missile"));
	missile->GetTransform().size *= 0.2f;
	missile->GetTransform().position = Vec2(500.0f);
	missile->GetTransform().rotation = glm::radians(30.0f);
	instantiateCallback(*missile);*/
}

rb::R2DScene::R2DScene(const R2DScene& rhs)
	:sceneObjects(rhs.sceneObjects),
	instantiateCallback(rhs.instantiateCallback)
{}
R2DScene& rb::R2DScene::operator=(const R2DScene& rhs)
{
	sceneObjects = rhs.sceneObjects;
	instantiateCallback = instantiateCallback;
	return *this;
}
rb::R2DScene::R2DScene(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	instantiateCallback = std::move(rhs.instantiateCallback);
}
R2DScene& rb::R2DScene::operator=(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	instantiateCallback = std::move(rhs.instantiateCallback);
	return *this;
}
GameObject rb::R2DScene::Instantiate(const GameObject& prefab)
{
	/*std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(prefab);
	sceneObjects.push_back(objClone);
	assert(instantiateCallback && "Instantiate callback is null");
	instantiateCallback(*objClone);
	return *objClone;*/
	return Instantiate(prefab, prefab.GetTransform().position, prefab.GetTransform().rotation);
}

rb::GameObject rb::R2DScene::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(prefab);
	objClone->SetTransform(position, rotation);
	sceneObjects.push_back(objClone);
	assert(instantiateCallback && "Instantiate callback is null");
	instantiateCallback(*objClone);
	return *objClone;
}

void rb::R2DScene::Update(float dt)
{

}




