#include "RenderEngine.h"
#include <assert.h>
#include <algorithm>
#include "RDebug.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
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

void rb::RenderEngine::PreRender() 
{
	glClearColor(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void RenderEngine::Render()
{
	const int numSprites = spriteRenderers.size();
	//Debug::Log("Num renderers: " + ToString(numSprites));
	if (numSprites == 0) return;

#if RENDER_MODE_IMMEDIATE
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
	}//for sprites
#endif //RENDER_MODE_IMMEDIATE

#if RENDER_MODE_INSTANCED

	SetupBatches();

	//foreach shader batch
	Debug::Log("Num shader batches: " + ToString(shaderBatches.size()));
	for (auto& shaderBatch : shaderBatches)
	{
		//bind shader
		auto& shader = shaderBatch->shader;
		shader.Use();
		//set uniforms for the entire texture batch
		shader.SetMat4(Shader::projUniformName, projection);
		
		//foreach tex batch
		for (auto& textureBatch: shaderBatch->textureBatches)
		{
			//bind texure
			shader.SetInt(Shader::spriteTextureName, 0);
			textureBatch->texture.Bind();

			//send model and colour arrays to shader
			GLuint VAO = textureBatch->VAO;
			GLuint modelMatBuffer, colourBuffer;
			const auto vec4Size = sizeof(Vec4);
			const auto numTexBatches = shaderBatch->textureBatches.size();
			
			glBindVertexArray(VAO);
			Debug::CheckOpenGLError();
			//model and colour buffers
			//colours
			glGenBuffers(1, &colourBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
			glBufferData(GL_ARRAY_BUFFER, numTexBatches * vec4Size, textureBatch->colours.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
			glVertexAttribDivisor(1, 1);

			//model mat buffer
			glGenBuffers(1, &modelMatBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, modelMatBuffer);
			glBufferData(GL_ARRAY_BUFFER, numTexBatches * sizeof(Mat4), textureBatch->modelMatrices.data(), GL_STATIC_DRAW);
			//model matrix is from 2..5
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)vec4Size);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2*vec4Size));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));
			glVertexAttribDivisor(2, 1);
			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			//instanced render
			Debug::Log("Num batches: " + ToString(numTexBatches));
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numTexBatches);
			Debug::CheckOpenGLError();
			glBindVertexArray(0);
			Texture::Unbind();
		}//for textureBatches
		Shader::Unbind();
	}//for shaderBatches
	ClearBatches();
			
#endif // RENDER_MODE_INSTANCED


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
#if RENDER_MODE_INSTANCED

void rb::RenderEngine::ClearBatches()
{
	/*for (auto& shaderBatch : shaderBatches)
	{
		shaderBatch->textureBatches.clear();
	}
	shaderBatches.clear();*/
	
	while (!shaderBatches.empty())
	{
		auto& textureBatch = shaderBatches[0]->textureBatches;
		while (!textureBatch.empty())
		{
			textureBatch.erase(textureBatch.begin() + textureBatch.size() - 1);
		}
		shaderBatches.erase(shaderBatches.begin() + shaderBatches.size() - 1);
	}
}

void rb::RenderEngine::SetupBatches()
{
	//sort sprites by shader first
	std::stable_sort(spriteRenderers.begin(), spriteRenderers.end(), 
		[](const std::shared_ptr<SpriteRenderer>& a, const std::shared_ptr<SpriteRenderer>& b)
	{
		return a->GetShader().Program() > b->GetShader().Program();
	});

	//setup the shader batches
	//add first shaderBatch with the first sprite's info
	shaderBatches.push_back(std::make_shared<ShaderBatch>(spriteRenderers[0]));

	//foreach sprite, add to existing or new shaderBatch
	for (size_t i = 1; i < spriteRenderers.size(); ++i)
	{
		//add to last shaderBatch if using the same shader
		if (spriteRenderers[i]->GetShader().Program() == shaderBatches.back()->shader.Program())
		{
			//same shader, so add a new textureBatch with this sprite's texture
			shaderBatches.back()->textureBatches.push_back(std::make_shared<TextureBatch>(spriteRenderers[i]));
		}
		else //new shader - create new shader batch and setup texture batches for previous shader batch
		{
			auto& shaderBatch = shaderBatches.back();
			//sort last shaderBatch's textureBatch by texture
			std::stable_sort(shaderBatch->textureBatches.begin(), shaderBatch->textureBatches.end(),
				[](const std::shared_ptr<TextureBatch>& a, const std::shared_ptr<TextureBatch>& b)
			{
				return a->texture.textureID > b->texture.textureID;
			});
			//foreach textureBatch, setup modelMatrices and colours
			for (size_t j = 1; j < shaderBatch->textureBatches.size(); )
			{
				auto& prevTexBatch = shaderBatch->textureBatches[j - 1];
				auto& thisTexBatch = shaderBatch->textureBatches[j];
				//if same texture as previous, get rid of this as it is repeated, but save model and colour into previous texBatch
				if (thisTexBatch->texture.textureID == prevTexBatch->texture.textureID)
				{
					assert(thisTexBatch->modelMatrices.size() == 1 && "Expecting tex batch to have one 1 model matrix at this point");
					assert(thisTexBatch->colours.size() == 1 && "Expecting tex batch to have one 1 colour at this point");
					prevTexBatch->modelMatrices.push_back(thisTexBatch->modelMatrices[0]);
					prevTexBatch->colours.push_back(thisTexBatch->colours[0]);
					//erase this tex patch as it is a duplicate
					shaderBatch->textureBatches.erase(shaderBatch->textureBatches.begin() + j);
					//j should not increment since an element was deleted
				}
				else
				{
					j++;
				}
			}//for textureBatches

			//create new shaderBatch with this sprite's shader
			shaderBatches.push_back(std::make_shared<ShaderBatch>(spriteRenderers[i]));
		}//end else (if not same shader)
	}//for sprites
}

//ShaderBatch Ctor
rb::RenderEngine::ShaderBatch::ShaderBatch(const std::shared_ptr<SpriteRenderer>& sprite)
	:shader(sprite->GetShader())
{
	textureBatches.push_back(std::make_shared<TextureBatch>(sprite));
}
//TextureBatch ctor
rb::RenderEngine::TextureBatch::TextureBatch(const std::shared_ptr<SpriteRenderer>& sprite)
	: texture(sprite->GetTexture()),
	VAO(sprite->VAO)
{
	modelMatrices.push_back(sprite->GetGameObject()->GetTransform()->GetTransformMatrix());
	colours.push_back(sprite->GetColour());
}
#endif // RENDER_MODE_INSTANCED

void rb::RenderEngine::PostRender() 
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


