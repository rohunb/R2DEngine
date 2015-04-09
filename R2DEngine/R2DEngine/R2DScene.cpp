#include "R2DScene.h"
#include "GameObject.h";

using namespace rb;

rb::R2DScene::R2DScene()
{

}
rb::R2DScene::R2DScene(const R2DScene& rhs)
	:sceneObjects(rhs.sceneObjects)
{}
R2DScene& rb::R2DScene::operator=(const R2DScene& rhs)
{
	sceneObjects = rhs.sceneObjects;
	return *this;
}
rb::R2DScene::R2DScene(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
}
R2DScene& rb::R2DScene::operator=(R2DScene&& rhs)
{
	sceneObjects = std::move(rhs.sceneObjects);
	return *this;
}
GameObject rb::R2DScene::Instantiate(const GameObject& prefab)
{
	std::shared_ptr<GameObject> objClone = std::make_shared<GameObject>(prefab);
	sceneObjects.push_back(objClone);
	return *objClone;
}

void rb::R2DScene::Update(float dt)
{

}




