#include "RInput.h"
#include "RDebug.h"

using namespace rb;

std::vector<std::function<void(int, int)>> rb::Input::OnKeyboardEvents;
std::vector <std::function<void(int, int, const Vec2&)>> rb::Input::OnMouseClickEvents;
rb::Vec2 rb::Input::mousePosition;

rb::Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMoveCallback);

	Debug::Log("Initialized Input System.");
}

void rb::Input::RegisterKeyCallback(std::function<void(int, int)> OnKeyboard)
{
	OnKeyboardEvents.push_back(OnKeyboard);
}

void rb::Input::RegisterMouseClickCallback(std::function<void(int button, int action, const Vec2& mousePos)> OnMouseClick)
{
	OnMouseClickEvents.push_back(OnMouseClick);
}

rb::Vec2 rb::Input::GetMousePosition()
{
	return mousePosition;
}

void rb::Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	for (auto event: OnKeyboardEvents)
	{
		event(key, action);
	}
}

void rb::Input::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	for (auto event: OnMouseClickEvents)
	{
		event(button, action, mousePosition);
	}
}

void rb::Input::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	//Debug::Log("mouse move " + ToString(xPos) + "m" + ToString(yPos));
	mousePosition = Vec2(static_cast<float>(xPos), static_cast<float>(yPos));
}
