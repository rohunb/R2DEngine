#ifndef R_INPUT_H_
#define R_INPUT_H_

#include <functional>
#include <glfw3.h>
#include "RCollections.h"

namespace rb
{
	class Input
	{
	public:
		
		Input(GLFWwindow* window);
		//static bool GetKeyDown(int key);
		static void RegisterKeyCallback(std::function<void(int key, int action)>);

	private:
		//static TArray<bool, 1024> keyStates;
		static std::function<void(int, int)> OnKeyboardEvent;
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	};
}
#endif // !R_INPUT_H_
