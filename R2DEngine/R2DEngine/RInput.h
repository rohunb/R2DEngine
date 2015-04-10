#ifndef R_INPUT_H_
#define R_INPUT_H_

#include <functional>
#include <glfw3.h>
#include <vector>
#include "RVector.h"

namespace rb
{
	class Input
	{
	public:

		Input(GLFWwindow* window);
		static void RegisterKeyCallback(std::function<void(int key, int action)>);
		static void RegisterMouseClickCallback(std::function<void(int button, int action, const Vec2& mousePos)>);
		static Vec2 GetMousePosition();

	private:
		static std::vector<std::function<void(int, int)>> OnKeyboardEvents;
		static std::vector<std::function<void(int, int, const Vec2&)>> OnMouseClickEvents;
		static Vec2 mousePosition;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
	};
}
#endif // !R_INPUT_H_
