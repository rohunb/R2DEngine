#include "R2DScene.h"
#include "GameObject.h"
#include "RDebug.h"
#include "TextureManager.h"

using namespace rb;

rb::R2DScene::R2DScene(std::function<void(GameObject&)> OnInstantiate)
	:OnInstantiate(OnInstantiate)
{}

rb::R2DScene::R2DScene(const R2DScene& rhs)
	:sceneObjects(rhs.sceneObjects),
	OnInstantiate(rhs.OnInstantiate)
{}
R2DScene& rb::R2DScene::operator=(const R2DScene& rhs)
{
	sceneObjects = rhs.sceneObjects;
	OnInstantiate = OnInstantiate;
	return *this;
}
rb::R2DScene::R2DScene(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	OnInstantiate = std::move(rhs.OnInstantiate);
}
R2DScene& rb::R2DScene::operator=(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	OnInstantiate = std::move(rhs.OnInstantiate);
	return *this;
}
std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab)
{
	return Instantiate(prefab, prefab.GetTransform()->position, prefab.GetTransform()->rotation);
}

std::shared_ptr<GameObject> rb::R2DScene::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(prefab);
	objClone->SetTransform(position, rotation);
	sceneObjects.push_back(objClone);
	assert(OnInstantiate && "Instantiate callback is null");
	OnInstantiate(*objClone);
	//Debug::Log("transform: " + ToString(objClone->transform.use_count()) + " sprite " + ToString(objClone->renderer.use_count()) + " rb " + ToString(objClone->rigidbody.use_count()));
	return objClone;
}

void rb::R2DScene::Update(float dt)
{

}




