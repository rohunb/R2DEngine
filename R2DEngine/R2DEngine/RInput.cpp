#include "RInput.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"

using namespace rb;

std::vector<KeyboardEvent> rb::Input::OnKeyboardEvents;
std::vector <MouseClickEvent> rb::Input::OnMouseClickEvents;

rb::Vec2 rb::Input::mousePosition;

rb::Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMoveCallback);

	Debug::Log("Initialized Input System.");
}

void rb::Input::RegisterKeyCallback(KeyboardEvent OnKeyboard)
{
	OnKeyboardEvents.push_back(OnKeyboard);
}

void rb::Input::RegisterMouseClickCallback(MouseClickEvent OnMouseClick)
{
	OnMouseClickEvents.push_back(OnMouseClick);
}

void rb::Input::ClearAllCallbacks()
{
	OnKeyboardEvents.clear();
	OnMouseClickEvents.clear();
}

//void rb::Input::RemoveKeyCallback(std::function<void(int key, int action)> OnKeyboard)
//{
//	assert(std::find(OnKeyboardEvents.begin(), OnKeyboardEvents.end(), OnKeyboard) != OnKeyboardEvents.end() && "OnKeyboard event not found");
//	OnKeyboardEvents.erase(std::remove(OnKeyboardEvents.begin(), OnKeyboardEvents.end(), OnKeyboard),
//							OnKeyboardEvents.end());
//}
//
//void rb::Input::RemoveMouseClickCallback(std::function<void(int button, int action, const Vec2& mousePos)> OnMouseClick)
//{
//	assert(std::find(OnMouseClickEvents.begin(), OnMouseClickEvents.end(), OnMouseClick) != OnMouseClickEvents.end() && "OnMouseClickEvent not found");
//	OnMouseClickEvents.erase(std::find(OnMouseClickEvents.begin(), OnMouseClickEvents.end(), OnMouseClick), 
//							OnMouseClickEvents.end());
//}

rb::Vec2 rb::Input::GetMousePosition()
{
	return mousePosition;
}

void rb::Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::for_each(OnKeyboardEvents.begin(),
		OnKeyboardEvents.end(),
		[=](const KeyboardEvent& event){event(key, action); });
}

void rb::Input::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::for_each(OnMouseClickEvents.begin(),
		OnMouseClickEvents.end(),
		[=](const MouseClickEvent& event){event(button, action, mousePosition); });
}

void rb::Input::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	//Debug::Log("mouse move " + ToString(xPos) + "m" + ToString(yPos));
	mousePosition = Vec2(static_cast<float>(xPos), static_cast<float>(yPos));
}
