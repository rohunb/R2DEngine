#ifndef R_INPUT_H_
#define R_INPUT_H_

#include <glfw3.h>
#include <functional>
#include <vector>
#include <memory>
#include "RVector.h"

namespace rb
{
	typedef std::function<void(int, int)> KeyboardEvent;
	typedef std::function<void(int, int, const Vec2&)> MouseClickEvent;

	class Input
	{
	public:
		Input(GLFWwindow* window);
		Input(const Input& rhs) = delete;
		Input(Input&& rhs) = delete;
		Input& operator = (const Input& rhs) = delete;
		Input& operator = (Input&& rhs) = delete;
		~Input() = default;

		static std::shared_ptr<KeyboardEvent> RegisterKeyCallback(KeyboardEvent OnKeyboard);
		static std::shared_ptr<MouseClickEvent> RegisterMouseClickCallback(MouseClickEvent OnMouseClick);

		static void ClearAllCallbacks();
		static void RemoveKeyCallback(std::shared_ptr<KeyboardEvent>& OnKeyboard);
		static void RemoveMouseClickCallback(std::shared_ptr<MouseClickEvent>& OnMouseClick);

		static Vec2 GetMousePosition();

	private:
		static std::vector<std::shared_ptr<KeyboardEvent>> keyboardEvents;
		static std::vector<std::shared_ptr<MouseClickEvent>> mouseClickEvents;
		static Vec2 mousePosition;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);
	};
}
#endif // !R_INPUT_H_
