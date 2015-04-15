#include "AnimatedSprite.h"
#include "ShaderManager.h"
#include "Screen.h"
#include "RMatrix.h"
#include "GameObject.h"

using namespace rb;

rb::AnimatedSprite::AnimatedSprite(const Texture& spriteSheet, int sheetWidth, int sheetHeight, int numFrames, float frameDuration, bool loop)
	:spriteSheet(spriteSheet), sheetWidth(sheetWidth), sheetHeight(sheetHeight), numFrames(numFrames), frameDuration(frameDuration), loop(loop)
{
	currFrame = 0;
	currentTime = 0.0f;
	shader = ShaderManager::GetShader(Shader::ShaderType::AnimatedSprite);
	colour = Colour::white;
	InitGL();
}

void rb::AnimatedSprite::Update(float dt)
{
	if (currentTime >= frameDuration)
	{
		currFrame = ++currFrame % numFrames;
		gridPos = Vec2(currFrame % sheetWidth, currFrame / sheetHeight);
		currentTime = 0.0f;
	}
	currentTime += dt;
}

void rb::AnimatedSprite::Render()
{
	shader.Use();
	Mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	shader.SetMat4(Shader::projUniformName, projection);
	//Mat4 modelMat = gameObject->GetTransform()->GetTransformMatrix();
	/*Mat4 modelMat = Mat4(1.0f);
	modelMat = glm::translate(modelMat, Vec3(400.0f));
	modelMat = glm::scale(modelMat, Vec3(200.0f));*/
	Mat4 modelMat = glm::translate(Mat4(1.0f),Vec3(700.0f, 300.0, 0.0f));
	//modelMat = glm::rotate(modelMat, rotation, RVector3::back);
	modelMat = glm::scale(modelMat, Vec3(100.0f));
	shader.SetMat4(Shader::modelUniformName, modelMat);
	shader.SetVec4(Shader::spriteColourName, colour.ToVec4());
	shader.SetInt("uWidth", sheetWidth);
	shader.SetInt("uHeight", sheetHeight);
	shader.SetVec2("uGridPos", gridPos);
	shader.SetInt(Shader::spriteTextureName, 0);
	spriteSheet.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	
	Texture::Unbind();
	Shader::Unbind();
}

void rb::AnimatedSprite::InitGL()
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
