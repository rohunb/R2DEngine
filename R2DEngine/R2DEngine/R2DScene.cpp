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
std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab)
{
	return Instantiate(prefab, prefab.transform->position, prefab.transform->rotation);
}

std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(prefab);
	Debug::Log("transform: " + ToString(objClone->transform.use_count()) + " sprite " + ToString(objClone->renderer.use_count()) + " rb " + ToString(objClone->rigidbody.use_count()));
	objClone->SetTransform(position, rotation);
	sceneObjects.push_back(objClone);
	assert(instantiateCallback && "Instantiate callback is null");
	instantiateCallback(*objClone);
	//Debug::Log("transform: " + ToString(objClone->transform.use_count()) + " sprite " + ToString(objClone->renderer.use_count()) + " rb " + ToString(objClone->rigidbody.use_count()));
	return objClone;
}

void rb::R2DScene::Update(float dt)
{

}




