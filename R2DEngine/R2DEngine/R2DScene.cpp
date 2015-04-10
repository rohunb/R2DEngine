#include "R2DScene.h"
#include "GameObject.h"
#include "RDebug.h"
#include "TextureManager.h"

using namespace rb;

rb::R2DScene::R2DScene(std::function<void(GameObject&)> instantiateCallback)
	:instantiateCallback(instantiateCallback)
{}

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




