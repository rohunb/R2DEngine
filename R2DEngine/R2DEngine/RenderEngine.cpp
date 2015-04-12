#include "RenderEngine.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

using namespace rb;

Colour RenderEngine::clearColour;

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
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	clearColour = Colour::darkGrey;
	projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight), -1.0f, 1.0f);
	Debug::Log("Initialized Render Engine.");
}

void rb::RenderEngine::PreRender() const
{
	glClearColor(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void RenderEngine::Render() const
{
	Debug::Log("Num renderers: " + ToString(spriteRenderers.size()));
	if (spriteRenderers.size() == 0) return;

	//////////////////////////////////////////////////////////////////////////
	//assuming all sprite use the same shader for now
	Shader shader = spriteRenderers[0]->GetShader();
	int numShadersOfSameType = std::count_if(spriteRenderers.begin(), spriteRenderers.end(),
		[&shader](const std::shared_ptr<SpriteRenderer>& spriteRenderer){return spriteRenderer->GetShader().Type() == shader.Type(); });
	assert(numShadersOfSameType == spriteRenderers.size() && "All Sprites must use the same shader");
	//////////////////////////////////////////////////////////////////////////

	shader.Use();
	for (auto& renderer: spriteRenderers)
	{
		auto trans = renderer->GetGameObject()->GetTransform();
		Mat4 modelMat = glm::translate(Mat4(1.0f), RVector2::ToVector3(trans->position));
		////translate to origin and rotate
		modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size * -0.5f));
		modelMat = glm::rotate(modelMat, trans->rotation, RVector3::back);
		modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size*0.5f));
		//scale to size
		modelMat = glm::scale(modelMat, Vec3(trans->size.x, trans->size.y, 1.0f));
		//set uniforms
		shader.SetMat4(Shader::modelUniformName, modelMat);
		shader.SetMat4(Shader::projUniformName, projection);
		shader.SetVec4(Shader::spriteColourName, renderer->GetColour().ToVec4());
		shader.SetInt(Shader::spriteTextureName, 0);
		renderer->GetTexture().Bind();
		//render
		renderer->Render();
		Texture::Unbind();
	}
	Shader::Unbind();
}
void rb::RenderEngine::PostRender() const
{
	glfwSwapBuffers(window);
}

void rb::RenderEngine::SetClearColour(const Colour& colour)
{
	clearColour = colour;
}

GLFWwindow* rb::RenderEngine::Window() const
{
	return window;
}

void rb::RenderEngine::AddNewRenderer(std::shared_ptr<class SpriteRenderer>& renderer)
{
	spriteRenderers.push_back(renderer);
}

void rb::RenderEngine::RemoveRenderer(std::shared_ptr<class SpriteRenderer>& renderer)
{
	assert(std::find(spriteRenderers.begin(), spriteRenderers.end(), renderer) != spriteRenderers.end() && "SpriteRenderer not present in RenderEngine");
	spriteRenderers.erase(std::remove(spriteRenderers.begin(), spriteRenderers.end(), renderer),
						spriteRenderers.end());
}
