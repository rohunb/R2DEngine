#include "RenderEngine.h"
#include "RDebug.h"

rb::RenderEngine::RenderEngine(int windowWidth, int windowHeight, int windowPosX, int windowPosY, string windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	int status = glewInit();
	glGetError();
	glViewport(windowPosX, windowPosY, windowWidth, windowHeight);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Debug::Log("Initialized Render Engine.");
}


void rb::RenderEngine::PreRender() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void rb::RenderEngine::PostRender() const
{
	glfwSwapBuffers(window);
}

GLFWwindow* rb::RenderEngine::Window() const
{
	return window;
}