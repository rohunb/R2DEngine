#ifndef R_R2D_GAME_H_
#define R_R2D_GAME_H_

#include <memory>
#include "R2DEngine.h"
#include "R2DScene.h"

namespace rb
{
	class R2DGame
	{
	public:
		//ctors
		R2DGame();
		R2DGame(const R2DGame& rhs) = delete;
		R2DGame(const R2DGame&& rhs) = delete;
		R2DGame& operator = (const R2DGame& rhs) = delete;
		R2DGame& operator = (const R2DGame&& rhs) = delete;
		virtual ~R2DGame() = default;

		//methods
		virtual void StartGame();
		virtual void Update(float dt);
		template<class T>
		std::shared_ptr<T> CreateNewScene();
		void LoadScene(std::shared_ptr<R2DScene> scene);

		//callbacks
		void OnKeyboard(int key, int action);

	private:
		std::unique_ptr<R2DEngine> engine;
		std::shared_ptr<R2DScene> currentScene;

		void LoadDefaultResources();
		void RegisterNewGameObject(class GameObject& gameObject);
		void DestroyGameObject(std::shared_ptr<class GameObject>& gameObject);
	};

	template<class T>
	std::shared_ptr<T> R2DGame::CreateNewScene()
	{
		static_assert(std::is_base_of<R2DScene, T>::value, "Must derive from R2DScene");

		std::shared_ptr<T> newScene = std::make_shared<T>();

		static_cast<R2DScene*>(newScene.get())->SetupCallbacks(
			[&](GameObject& go){RegisterNewGameObject(go); },
			[&](std::shared_ptr<GameObject>& go){DestroyGameObject(go); });

		return newScene;
	}
}
#endif // !R_R2D_GAME_H_
