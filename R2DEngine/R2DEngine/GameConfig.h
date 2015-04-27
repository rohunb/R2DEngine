#ifndef R_GAME_CONFIG_H_
#define R_GAME_CONFIG_H_

#include "RString.h"

namespace rb
{
#define PHYSICS_DEBUG_DRAW 0 //only works with immediate mode
#define RENDER_MODE_IMMEDIATE 1
#define RENDER_MODE_INSTANCED 0

	struct GameConfig
	{
		static const int windowWidth;
		static const int windowHeight;
		static const int windowPosX ;
		static const int windowPosY ;
		static const string windowName;
	};
}
#endif // !R_GAME_CONFIG_H_
