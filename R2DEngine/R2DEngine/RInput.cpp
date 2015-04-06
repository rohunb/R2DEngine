#include "RInput.h"
#include "RDebug.h"

using namespace rb;

TArray<bool, 1024> rb::Input::keyStates;


rb::Input::Input(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	Debug::Log("Initialized Input System.");
}

bool rb::Input::GetKeyDown(int key)
{
	return keyStates[key];
}


void rb::Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		keyStates[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyStates[key] = false;
	}
}

void rb::Input::MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{

}
