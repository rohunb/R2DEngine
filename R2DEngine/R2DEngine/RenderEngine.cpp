#include "RenderEngine.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "GameConfig.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CircleCollider.h"

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
	const int numSprites = spriteRenderers.size();
	//Debug::Log("Num renderers: " + ToString(numSprites));
	if (numSprites == 0) return;


	for (auto& renderer : spriteRenderers)
	{
		auto& shader = renderer->GetShader();
		shader.Use();
		shader.SetMat4(Shader::projUniformName, projection);
		Mat4 modelMat = renderer->GetGameObject()->GetTransform()->GetTransformMatrix();
		//set uniforms
		shader.SetMat4(Shader::modelUniformName, modelMat);
		shader.SetVec4(Shader::spriteColourName, renderer->GetColour().ToVec4());
		shader.SetInt(Shader::spriteTextureName, 0);
		renderer->GetTexture().Bind();
		if (renderer->IsAnimated())
		{
			auto& anim = renderer->GetGameObject()->GetAnimator();
			assert(anim && "Sprite is marked as animation but has no Animator");
			if (!anim->IsAnimationComplete())
			{
				anim->SetShaderValues(shader);
			}
		}
		//render
		renderer->Render();
		Texture::Unbind();
		Shader::Unbind();

#if PHYSICS_DEBUG_DRAW
		/*if (renderer->IsAnimated())
		{
		Debug::Log("animated");
		}*/
		auto& col = std::dynamic_pointer_cast<CircleCollider>(renderer->GetGameObject()->GetCollider());
		if (col)
		{
			Shader colShader = ShaderManager::GetShader(Shader::ShaderType::SpriteShader);
			colShader.Use();
			colShader.SetMat4(Shader::projUniformName, projection);
			auto& trans = renderer->GetGameObject()->GetTransform();
			Mat4 modelMat = glm::translate(Mat4(1.0f), RVector2::ToVector3(trans->position));
			modelMat = glm::rotate(modelMat, trans->rotation, RVector3::back);
			modelMat = glm::scale(modelMat, Vec3(col->GetRadius(), col->GetRadius(), 1.0f));
			colShader.SetMat4(Shader::modelUniformName, modelMat);
			colShader.SetVec4(Shader::spriteColourName, Colour::red.ToVec4());
			colShader.SetInt(Shader::spriteTextureName, 0);
			TextureManager::GetTexture("CircleCollider").Bind();
			//Debug::Log("render col");
			renderer->Render();
			Texture::Unbind();
			Shader::Unbind();
		}
#endif // PHYSICS_DEBUG_DRAW
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



}
void rb::RenderEngine::SortSprites()
{
	
}


void rb::RenderEngine::SetupBatches()
{
	//clear batches
	for (auto& shaderBatch: shaderBatches)
	{
		shaderBatch->textureBatches.clear();
	}
	shaderBatches.clear();
	
	//sort sprites by shader first
	std::stable_sort(spriteRenderers.begin(), spriteRenderers.end(), 
		[](const std::shared_ptr<SpriteRenderer>& a, const std::shared_ptr<SpriteRenderer>& b)
	{
		return a->GetShader().Program() > b->GetShader().Program();
	});

	//setup the shader batches
	//add first shaderBatch with the first sprite's info
	shaderBatches.push_back(std::make_shared<ShaderBatch>(spriteRenderers[0]->GetShader()));
	for (size_t i = 1; i < spriteRenderers.size(); ++i)
	{
		//add to last shaderBatch if using the same shader
		if (spriteRenderers[i]->GetShader().Program() == shaderBatches.back()->shader.Program())
		{
			shaderBatches.back()->textureBatches.push_back(std::make_shared<TextureBatch>(spriteRenderers[i]->GetTexture().textureID));
		}
		else //new shaderBatch - setup texture batches for previous shader batch
		{
			auto& shaderBatch = shaderBatches.back();

			//sort 
		}
	}
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
