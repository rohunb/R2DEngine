#include "SpriteRenderer.h"
#include "RMatrix.h"
#include "Transform.h"
#include "GameObject.h"
#include "ShaderManager.h"
#include "RDebug.h"
#include "GameConfig.h"
#include "SOIL.h"

using namespace rb;

rb::SpriteRenderer::SpriteRenderer(const Texture& texture, const Shader& shader)
	: texture(texture), shader(shader)
{
	//Debug::Log("Tex Width: " + ToString(texture.width) + "," + ToString(texture.height));
	InitGL();
}

rb::SpriteRenderer::SpriteRenderer(const Texture& texture)
	:SpriteRenderer(texture,
	ShaderManager::GetShader(Shader::ShaderType::SpriteShader))
{}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &VAO);
}

rb::Texture rb::SpriteRenderer::GetTexture() const
{
	return texture;
}

void rb::SpriteRenderer::Render()
{
	shader.Use();
	auto trans = std::make_shared<Transform>(GetGameObject().GetTransform());
	Mat4 modelMat = glm::translate(Mat4(1.0f), RVector2::ToVector3(trans->position));
	////translate to origin and rotate
	modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size * -0.5f));
	modelMat = glm::rotate(modelMat, trans->rotation, RVector3::back);
	modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size*0.5f));
	//scale to size
	modelMat = glm::scale(modelMat, Vec3(trans->size.x, trans->size.y, 1.0f));

	//set uniforms
	Mat4 projection = glm::ortho(0.0f, static_cast<float>(GameConfig::windowWidth), 0.0f, static_cast<float>(GameConfig::windowHeight), -1.0f, 1.0f);

	shader.SetMat4(Shader::modelUniformName, modelMat);
	shader.SetMat4(Shader::projUniformName, projection);
	shader.SetVec4(Shader::spriteColourName, colour.ToVec4());
	shader.SetInt(Shader::spriteTextureName, 0);
	texture.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	Texture::Unbind();
	Shader::Unbind();
}

void rb::SpriteRenderer::InitGL()
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos       // Tex
		-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
