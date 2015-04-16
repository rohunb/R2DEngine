#ifndef R_GAME_OBJECT_H_
#define R_GAME_OBJECT_H_

#include <memory>
#include <vector>
#include <type_traits>
#include "RString.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Rigidbody2D.h"
#include "SpriteAnimator.h"
#include "Collider.h"

namespace rb
{
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		string name;
		string tag;
		bool destroyed=false;

		//ctors
		GameObject();
		explicit GameObject(const Texture& texture);
		GameObject(const GameObject& rhs);
		GameObject(GameObject&& rhs) ;
		GameObject& operator = (const GameObject& rhs);
		GameObject& operator = (GameObject&& rhs);
		~GameObject() = default;

		//get/set
		std::shared_ptr<Transform> GetTransform() const;
		std::shared_ptr<SpriteRenderer> GetRenderer() const;
		std::shared_ptr<Rigidbody2D> GetRigidbody() const;
		std::shared_ptr<SpriteAnimator> GetAnimator() const;
		std::shared_ptr<Collider> GetCollider() const;

		void SetTransform(const Vec2& position, float rotation = 0.0f);
		void SetTransform(const Vec2& position, float rotation, const Vec2& size);
		std::vector<std::shared_ptr<class R2DScript>> GetScripts() const;

		//methods
		void Init();

		template<class T>
		std::shared_ptr<T> AddComponent();
		template<class T>
		std::shared_ptr<T> GetComponent();
		template<class T>
		std::shared_ptr<T> AddScript();
		template<class T>
		std::shared_ptr<T> GetScript();
		
	private:
		std::vector<std::shared_ptr<class R2DScript>> scripts;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<SpriteRenderer> renderer;
		std::shared_ptr<Rigidbody2D> rigidbody;
		std::shared_ptr<SpriteAnimator> animator;
		std::shared_ptr<Collider> collider;
	};

	template<class T>
	std::shared_ptr<T> GameObject::AddScript()
	{
		static_assert(std::is_base_of<R2DScript, T>::value, "Script must inherit from R2DScript");
		auto newScript = std::make_shared<T>();
		scripts.push_back(newScript);
		
		return newScript;
	}
	template<class T>
	std::shared_ptr<T> GameObject::GetScript()
	{
		static_assert(std::is_base_of<R2DScript, T>::value, "Script must inherit from R2dscript");
		for (auto& script: scripts)
		{
			if (dynamic_cast<T*>(script.get()))
			{
				return std::dynamic_pointer_cast<T>(script);
			}
		}
		return nullptr;
	}


}

#endif // R_GAME_OBJECT_H_
