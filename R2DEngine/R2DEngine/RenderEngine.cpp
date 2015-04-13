#include "RenderEngine.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "GameConfig.h"

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
	glFrontFace(GL_CCW);
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
	int numSprites = spriteRenderers.size();
	//Debug::Log("Num renderers: " + ToString(numSprites));
	if (numSprites == 0) return;

	//////////////////////////////////////////////////////////////////////////
	//assuming all sprite use the same shader for now
	Shader shader = spriteRenderers[0]->GetShader();
	int numShadersOfSameType = std::count_if(spriteRenderers.begin(), spriteRenderers.end(),
		[&shader](const std::shared_ptr<SpriteRenderer>& spriteRenderer){return spriteRenderer->GetShader().Type() == shader.Type(); });
	assert(numShadersOfSameType == numSprites && "All Sprites must use the same shader");
	//////////////////////////////////////////////////////////////////////////
	shader.Use();
	shader.SetMat4(Shader::projUniformName, projection);
	
	for (auto& renderer : spriteRenderers)
	{
		Mat4 modelMat = renderer->GetGameObject()->GetTransform()->GetTransformMatrix();
		//set uniforms
		shader.SetMat4(Shader::modelUniformName, modelMat);
		shader.SetVec4(Shader::spriteColourName, renderer->GetColour().ToVec4());
		shader.SetInt(Shader::spriteTextureName, 0);
		renderer->GetTexture().Bind();
		//render
		renderer->Render();
		Texture::Unbind();
	}

	//////////////////////////////////////////////////////////////////////////
	//Point Sprite
	/*std::vector<Vec2> positions;
	std::vector<Vec2> sizes;
	const GLsizeiptr verticesLength = numSprites * sizeof(Vec2);
	positions.reserve(numSprites);
	sizes.reserve(numSprites);
	for (auto& sprite: spriteRenderers)
	{
		positions.push_back(sprite->GetGameObject()->GetTransform()->position);
		sizes.push_back(sprite->GetGameObject()->GetTransform()->size);
	}
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesLength * 2.0f, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticesLength, &positions[0]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glBufferSubData(GL_ARRAY_BUFFER, verticesLength, verticesLength, &sizes[0]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)verticesLength);

	glDrawArrays(GL_POINTS, 0, numSprites);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/

	//////////////////////////////////////////////////////////////////////////

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
