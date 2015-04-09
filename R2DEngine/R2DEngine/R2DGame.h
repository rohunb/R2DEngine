#ifndef R_R2D_GAME_H_
#define R_R2D_GAME_H_

#include <memory>
#include "R2DEngine.h"
#include "GameObject.h"

namespace rb
{
	class R2DGame
	{
	public:
		R2DGame();
		R2DGame(const R2DGame& rhs) = delete;
		R2DGame(const R2DGame&& rhs) = delete;
		R2DGame& operator = (const R2DGame& rhs) = delete;
		R2DGame& operator = (const R2DGame&& rhs) = delete;
		virtual ~R2DGame() = default;

		virtual void StartGame();
		virtual void Render();
		virtual void Update(float dt);
		void OnKeyboard(int key, int action);

	private:
		std::unique_ptr<R2DEngine> engine;
		//temp
		std::shared_ptr<GameObject> missile;
		std::shared_ptr<GameObject> asteroid;

		void LoadDefaultResources();
	};
}
#endif // !R_R2D_GAME_H_
