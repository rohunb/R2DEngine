#ifndef R_ROCKET_COMMAND_H_
#define R_ROCKET_COMMAND_H_

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

	private:
		std::shared_ptr<class R2DScene> testScene;
		std::unique_ptr<class GameObject> missilePrefab;
		Vec2 cannonPos;
		float missileSpeed;

		void LoadResources();
		void OnKeyboard(int key, int action);
		void OnMouseClick(int button, int action, const Vec2& mousePosition);
	};
}

#endif // !R_ROCKET_COMMAND_H_
