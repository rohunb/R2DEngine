#ifndef R_INPUT_H_
#define R_INPUT_H_

#include <functional>
#include <glfw3.h>
#include <vector>
#include "RVector.h"

namespace rb
{
	typedef std::function<void(int, int)> KeyboardEvent;
	typedef std::function<void(int, int, const Vec2&)> MouseClickEvent;

	class Input
	{
	public:
		Input(GLFWwindow* window);
		static void RegisterKeyCallback(KeyboardEvent OnKeyboard);
		static void RegisterMouseClickCallback(MouseClickEvent OnMouseClick);
		
		static void ClearAllCallbacks();

		/*static void RemoveKeyCallback(std::function<void(int key, int action)> OnKeyboard);
		static void RemoveMouseClickCallback(std::function<void(int button, int action, const Vec2& mousePos)> OnMouseClick);*/

		static Vec2 GetMousePosition();

	private:
		static std::vector<KeyboardEvent> OnKeyboardEvents;
		static std::vector<MouseClickEvent> OnMouseClickEvents;
		static Vec2 mousePosition;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
	};
}
#endif // !R_INPUT_H_
