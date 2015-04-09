#ifndef R_TD_GAME_H_
#define R_TD_GAME_H_

#include "R2DGame.h"

namespace rb
{
	class TowerDefenseGame : public R2DGame
	{
	public:
		TowerDefenseGame();
		TowerDefenseGame(const TowerDefenseGame& rhs) = delete;
		TowerDefenseGame(const TowerDefenseGame&& rhs) = delete;
		TowerDefenseGame& operator = (const TowerDefenseGame& rhs) = delete;
		TowerDefenseGame& operator = (const TowerDefenseGame&& rhs) = delete;
		virtual ~TowerDefenseGame() = default;
		
		virtual void StartGame() override;
		virtual void Render() override;
		virtual void Update(float dt) override;
	private:

	};
}

#endif // !R_TD_GAME_H_
