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
	: texture(texture), shader(shader), colour(Colour::white)
{
	InitGL();
}
rb::SpriteRenderer::SpriteRenderer(const Texture& texture)
	: SpriteRenderer(texture,
	ShaderManager::GetShader(Shader::ShaderType::SpriteShader))
{}

rb::SpriteRenderer::SpriteRenderer(const SpriteRenderer&& rhs)
	:shader(std::move(rhs.shader)),
	texture(std::move(rhs.texture)),
	colour(std::move(rhs.colour)),
	VAO(std::move(rhs.VAO))
{}

SpriteRenderer& rb::SpriteRenderer::operator=(const SpriteRenderer&& rhs)
{
	shader = std::move(rhs.shader);
	texture = std::move(rhs.texture);
	colour = std::move(rhs.colour);
	VAO = std::move(rhs.VAO);
	return *this;
}



SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &VAO);
}

rb::Texture rb::SpriteRenderer::GetTexture() const
{
	return texture;
}

Shader rb::SpriteRenderer::GetShader() const
{
	return shader;
}

rb::Colour rb::SpriteRenderer::GetColour() const
{
	return colour;
}

void rb::SpriteRenderer::SetColour(const Colour& val)
{
	colour = val;
}

bool rb::SpriteRenderer::IsAnimated() const
{
	return animated;
}

void rb::SpriteRenderer::EnableAnimation()
{
	shader = ShaderManager::GetShader(Shader::ShaderType::AnimatedSprite);
	animated = true;
}

void rb::SpriteRenderer::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void rb::SpriteRenderer::InitGL()
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos       // Tex
		-0.5f, 0.5f, 0.0f, 0.0f, //left top
		-0.5f, -0.5f, 0.0f, 1.0f, //left bot
		0.5f, 0.5f, 1.0f, 0.0f, //right top
		0.5f, -0.5f, 1.0f, 1.0f, //right bot

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
