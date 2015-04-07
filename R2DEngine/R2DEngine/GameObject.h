#ifndef R_GAME_OBJECT_H_
#define R_GAME_OBJECT_H_

#include "RString.h"
#include "RCollections.h"
#include "RMemory.h"
#include "R2DComponent.h"
#include "Transform.h"

namespace rb
{
	class GameObject
	{
	public:
		string name;
		string tag;

		GameObject();
		GameObject(const GameObject& rhs);
		GameObject(GameObject&& rhs);
		GameObject& operator = (const GameObject& rhs);
		GameObject& operator = (GameObject&& rhs);
		~GameObject();

		template <class T>
		T GetComponent();

		void Destroy();

	private:
		TVector<SharedPtr<R2DComponent>> components;
		SharedPtr<Transform> transform;
	};
}

#endif // R_GAME_OBJECT_H_
