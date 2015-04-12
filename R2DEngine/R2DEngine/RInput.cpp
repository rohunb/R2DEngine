#include "RInput.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"

using namespace rb;

std::vector<std::shared_ptr<KeyboardEvent>> rb::Input::keyboardEvents;
std::vector<std::shared_ptr<MouseClickEvent>> rb::Input::mouseClickEvents;
rb::Vec2 rb::Input::mousePosition;

rb::Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseClickCallback);
	glfwSetCursorPosCallback(window, MouseMoveCallback);

	Debug::Log("Initialized Input System.");
}

std::shared_ptr<KeyboardEvent> rb::Input::RegisterKeyCallback(KeyboardEvent OnKeyboard)
{
	auto eventPtr = std::make_shared<KeyboardEvent>(OnKeyboard);
	keyboardEvents.push_back(eventPtr);
	return eventPtr;
}

std::shared_ptr<MouseClickEvent> rb::Input::RegisterMouseClickCallback(MouseClickEvent OnMouseClick)
{
	auto eventPtr = std::make_shared<MouseClickEvent>(OnMouseClick);
	mouseClickEvents.push_back(eventPtr);
	return eventPtr;
}

void rb::Input::ClearAllCallbacks()
{
	keyboardEvents.clear();
	mouseClickEvents.clear();
}

void rb::Input::RemoveKeyCallback(std::shared_ptr<KeyboardEvent>& OnKeyboard)
{
	assert(std::find(keyboardEvents.begin(), keyboardEvents.end(), OnKeyboard) != keyboardEvents.end() && "OnKeyboard not found");
	keyboardEvents.erase(std::remove(keyboardEvents.begin(), keyboardEvents.end(), OnKeyboard), 
						keyboardEvents.end());
}

void rb::Input::RemoveMouseClickCallback(std::shared_ptr<MouseClickEvent>& OnMouseClick)
{
	assert(std::find(mouseClickEvents.begin(), mouseClickEvents.end(), OnMouseClick) != mouseClickEvents.end() && "OnMouseClick event not found");
	mouseClickEvents.erase(std::remove(mouseClickEvents.begin(), mouseClickEvents.end(), OnMouseClick), 
						mouseClickEvents.end());
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
	std::for_each(keyboardEvents.begin(),
		keyboardEvents.end(),
		[=](const std::shared_ptr<KeyboardEvent>& eventPtr){(*eventPtr)(key, action); });
}

void rb::Input::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	std::for_each(mouseClickEvents.begin(),
		mouseClickEvents.end(),
		[=](const std::shared_ptr<MouseClickEvent>& eventPtr){(*eventPtr)(button, action, mousePosition); });
}

void rb::Input::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	//Debug::Log("mouse move " + ToString(xPos) + "m" + ToString(yPos));
	mousePosition = Vec2(static_cast<float>(xPos), static_cast<float>(yPos));
}
