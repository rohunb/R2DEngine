#include "R2DScript.h"
#include "R2DScene.h"

using namespace rb;

void rb::R2DScript::Start()
{

}

void rb::R2DScript::Update(float dt)
{

}

void rb::R2DScript::OnDestroy()
{

}

std::shared_ptr<GameObject> rb::R2DScript::Instantiate(const GameObject& prefab)
{
	return Instantiate(prefab, prefab.GetTransform()->position, prefab.GetTransform()->rotation);
}

void rb::R2DScript::Destroy(std::shared_ptr<GameObject>& gameObject)
{
	//currentScene->Destroy(gameObject);
	gameObject->destroyed = true;
}

std::shared_ptr<GameObject> rb::R2DScript::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	assert(currentScene && "Current scene is null");
	return currentScene->Instantiate(prefab, position, rotation);
}
