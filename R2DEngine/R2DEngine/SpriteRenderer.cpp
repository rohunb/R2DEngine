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
	Debug::Log("SpriteRenderer ctor");
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
void rb::SpriteRenderer::Render()
{
	shader.Use();
	auto trans = std::make_shared<Transform>(GetGameObject().GetTransform());
	Mat4 modelMat = Mat4(1.0f);
	modelMat = glm::translate(modelMat, Vec3(900.0f, 500.0f, 0.0f));
	//Mat4 modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->position));
	//////translate to origin and rotate
	//modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size * 0.5f));
	//modelMat = glm::rotate(modelMat, trans->rotation, RVector3::back);
	//modelMat = glm::translate(modelMat, RVector2::ToVector3(trans->size*-0.5f));
	//scale to size
	modelMat = glm::scale(modelMat, Vec3(100.0f));

	//set uniforms
	Mat4 projection = glm::ortho(0.0f, static_cast<float>(GameConfig::windowWidth), 0.0f, static_cast<float>(GameConfig::windowHeight), -1.0f, 1.0f);
	//Mat4 projection = glm::perspective(53.13f, 16.0f / 9.0f, 0.1f, 1000.0f);
	//glm::mat4 projection = glm::ortho(0.f, 400.0f, 0.f, 400.0f, -1.f, 1.f);
	/*glUniformMatrix4fv(glGetUniformLocation(shader.Program(), "uModel"),1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program(), "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));*/
	shader.SetMat4(Shader::modelUniformName, modelMat);
	shader.SetMat4(Shader::projUniformName, projection);
	colour = Colour::green;
	shader.SetVec4(Shader::spriteColourName, colour.ToVec4());
	shader.SetInt(Shader::spriteTextureName, 0);
	texture.Bind();

	/*Debug::Log("Set tex ID: " + ToString(texture.textureID));
	GLint texLoc = glGetUniformLocation(shader.Program(), "uTexture");
	glUniform1i(texLoc, 0);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);*/
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	Texture::Unbind();
	Shader::Unbind();
}

void rb::SpriteRenderer::InitGL()
{
	//GLuint VBO;
	//GLfloat vertices[] = {
	//	// Pos      // UV
	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 0.0f,

	//	0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f, 1.0f,
	//	1.0f, 0.0f, 1.0f, 0.0f
	//};
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindVertexArray(VAO);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		/*0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.0f, 1.0f, 0.0f*/
		
		/*0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f*/

		//0.0f,0.0f, 0.0f,0.0f, //bot left
		//0.0f,1.0f,0.0f,1.0f, //top left
		//1.0f,0.0f,1.0f,0.0f, //bot right
		//1.0f,1.0f,1.0f,1.0f  //top right

		-0.5f,-0.5f,0.0f,1.0f,
		-0.5f,0.5f,0.0f,0.0f,
		0.5f,-0.5f,1.0f,1.0f,
		0.5f,0.5f,1.0f,0.0f

		//working
		/*0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f*/
		
		//0.0f, 1.0f, 0.0f, 1.0f, //top left
		//1.0f, 0.0f, 1.0f, 0.0f, //bot right
		//0.0f, 0.0f, 0.0f, 0.0f, //bot left

		//0.0f, 1.0f, 0.0f, 1.0f, //top left
		//1.0f, 1.0f, 1.0f, 1.0f, //top right
		//1.0f, 0.0f, 1.0f, 0.0f //bot right


		//0.0f, 0.0f, 0.0f, 0.0f,//bot left
		//1.0f, 0.0f, 1.0f, 0.0f, //bot right
		//0.0f, 1.0f, 0.0f, 1.0f,//top left

		//0.0f, 1.0f, 0.0f, 1.0f,//top left
		//1.0f, 0.0f, 1.0f, 0.0f, //bot right
		//1.0f, 1.0f, 1.0f, 1.0f// top right

		////working
		//0.0f, 0.0f, 0.0f, 1.0f,//bot left
		//0.0f, 1.0f, 0.0f, 0.0f,//top left
		//1.0f, 0.0f, 1.0f, 1.0f, //bot right

		//1.0f, 0.0f, 1.0f, 1.0f, //bot right
		//0.0f, 1.0f, 0.0f, 0.0f,//top left
		//1.0f, 1.0f, 1.0f, 0.0f// top right
	};

	/*GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
	};*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//int width, height;
	///*unsigned char* image = SOIL_load_image("basketball-floor-texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);*/
	//unsigned char* image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGBA);
	//glBindTexture(GL_TEXTURE_2D, texID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, 0);
}
