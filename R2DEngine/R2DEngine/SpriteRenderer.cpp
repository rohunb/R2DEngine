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

Shader rb::SpriteRenderer::GetShader() const
{
	return shader;
}

rb::Colour rb::SpriteRenderer::GetColour() const
{
	return colour;
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
		/*-0.5f, -0.5f, 0.0f, 1.0f, 
		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 0.0f*/

		//-0.5f, 0.5f, 0.0f, 1.0f, //left top
		//-0.5f, -0.5f, 0.0f, 0.0f, //left bot
		//0.5f, 0.5f, 1.0f, 1.0f, //right top
		//0.5f, -0.5f, 1.0f, 0.0f //right bot

		-0.5f, 0.5f, 0.0f, -1.0f, //left top
		-0.5f, -0.5f, 0.0f, 0.0f, //left bot
		0.5f, 0.5f, 1.0f, -1.0f, //right bot
		0.5f, -0.5f, 1.0f, 0.0f, //right top

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
