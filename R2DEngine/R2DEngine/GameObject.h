#ifndef R_GAME_OBJECT_H_
#define R_GAME_OBJECT_H_

#include <memory>
#include <vector>
#include "RString.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Rigidbody2D.h"

namespace rb
{
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		string name;
		string tag;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<SpriteRenderer> renderer;
		std::shared_ptr<Rigidbody2D> rigidbody;

		//ctors
		GameObject();
		explicit GameObject(const Texture& texture);
		GameObject(const GameObject& rhs);
		GameObject(GameObject&& rhs);
		GameObject& operator = (const GameObject& rhs);
		GameObject& operator = (GameObject&& rhs);
		~GameObject();

		//get/set
		/*Transform& GetTransform() const;
		SpriteRenderer& GetRenderer() const;*/
		void SetTransform(const Vec2& position, float rotation);
		void SetTransform(const Vec2& position, float rotation, const Vec2& size);
		//methods
		void Init();
		void Destroy();

	//private:
		//std::vector<std::shared_ptr<R2DComponent>> components;
		
	};
}

#endif // R_GAME_OBJECT_H_
