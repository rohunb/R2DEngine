#include "R2DScript.h"
#include "R2DScene.h"

using namespace rb;

std::shared_ptr<GameObject> rb::R2DScript::Instantiate(const GameObject& prefab)
{
	return Instantiate(prefab, prefab.GetTransform()->position, prefab.GetTransform()->rotation);
}

std::shared_ptr<GameObject> rb::R2DScript::Instantiate(const GameObject& prefab, const Vec2& position, float rotation)
{
	assert(currentScene && "Current scene is null");
	return currentScene->Instantiate(prefab, position, rotation);
}
