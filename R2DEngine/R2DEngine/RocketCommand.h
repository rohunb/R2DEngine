#ifndef R_TD_GAME_H_
#define R_TD_GAME_H_

#include "R2DGame.h"

namespace rb
{
	class RocketCommand : public R2DGame
	{
	public:
		RocketCommand();
		RocketCommand(const RocketCommand& rhs) = delete;
		RocketCommand(const RocketCommand&& rhs) = delete;
		RocketCommand& operator = (const RocketCommand& rhs) = delete;
		RocketCommand& operator = (const RocketCommand&& rhs) = delete;
		virtual ~RocketCommand() = default;
		
		virtual void StartGame() override;
		//virtual void Update(float dt) override;
	private:

	};
}

#endif // !R_TD_GAME_H_
