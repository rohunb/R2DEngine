#ifndef R_R2D_SCENE_H_
#define R_R2D_SCENE_H_

#include <vector>
#include <functional>
#include "GameObject.h"
#include "RVector.h"

namespace rb
{
	class R2DScene
	{
	public:
		//ctors
		R2DScene(std::function<void(GameObject&)> OnInstantiate, std::function<void(std::shared_ptr<GameObject>&)> OnDestroy);
		R2DScene(const R2DScene& rhs);
		R2DScene(R2DScene&& rhs);
		R2DScene& operator = (const R2DScene& rhs);
		R2DScene& operator = ( R2DScene&& rhs);
		~R2DScene() = default;

		//get/set
		Colour BackgroundColour() const;
		void BackgroundColour(const Colour& val);

		//methods
		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab);
		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab, const Vec2& position, float rotation);
		void Destroy(std::shared_ptr<GameObject>& gameObject);
		virtual void Update(float dt);

	protected:

	private:
		Colour backgroundColour;
		
		std::vector<std::shared_ptr<GameObject>> sceneObjects;
		std::function<void(GameObject&)> OnInstantiate;
		std::function<void(std::shared_ptr<GameObject>&)> OnDestroy;
	};
}

#endif // R_R2D_SCENE_H_