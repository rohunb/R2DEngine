#ifndef R_R2D_GAME_H_
#define R_R2D_GAME_H_

#include "RMemory.h"
#include "R2DEngine.h"

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
		virtual void Update(float dt);

	private:
		UniquePtr<R2DEngine> engine;
		
	};
}
#endif // !R_R2D_GAME_H_
