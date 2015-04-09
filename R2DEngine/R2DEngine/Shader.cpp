#include "Shader.h"
#include <fstream>
#include <assert.h>
#include "RDebug.h"
#include "FileManager.h"

using namespace rb;

const string& Shader::modelUniformName = "uModel";
const string& Shader::projUniformName = "uProjection";
const string& Shader::spriteTextureName = "uTexture";
const string& Shader::spriteColourName = "uColour";

rb::Shader::Shader(const string& vertexFileName, const string& fragmentFileName, ShaderType type)
	: Shader(vertexFileName, fragmentFileName, "", type)
{}

rb::Shader::Shader(const string& vertexFileName, const string& fragmentFileName, const string& geometryFileName, ShaderType type)
	: type(type)
{
	ProcessShader(
		vertexFileName.c_str(), 
		fragmentFileName.c_str(), 
		geometryFileName.empty()? nullptr : geometryFileName.c_str());
}

GLuint rb::Shader::Program() const
{
	return program;
}

rb::Shader::ShaderType rb::Shader::Type() const
{
	return type;
}

void rb::Shader::Use() const
{
	glUseProgram(program);
}

void rb::Shader::Unbind()
{
	glUseProgram(0);
}

void rb::Shader::SetFloat(const string& uniformName, float value)
{
	glUniform1f(GetUniformLoc(uniformName), value);
}

void rb::Shader::SetInt(const string& uniforName, int value)
{
	glUniform1i(GetUniformLoc(uniforName), value);
}

void rb::Shader::SetVec3(const string& uniformName, const Vec3& value)
{
	glUniform3f(GetUniformLoc(uniformName), value.x, value.y, value.z);
}

void rb::Shader::SetVec4(const string& uniformName, const Vec4& value)
{
	glUniform4f(GetUniformLoc(uniformName), value.x, value.y, value.z, value.w);
}

void rb::Shader::SetMat4(const string& uniformName, const Mat4& value)
{
	glUniformMatrix4fv(GetUniformLoc(uniformName), 1, GL_FALSE, glm::value_ptr(value));
}

GLint rb::Shader::GetUniformLoc(const string& uniformName)
{
	GLint loc = glGetUniformLocation(program, uniformName.c_str());
	//if (loc < 0) Debug::Error(uniformName);
	//assert(loc >= 0 && "Uniform location not found");
	return loc;
}

void rb::Shader::ProcessShader(const char* vertSource, const char* fragSource, const char* geomSource /*= nullptr*/)
{
	GLuint vertShader, fragShader, geomShader;
	
	//vertex shader
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, nullptr);
	glCompileShader(vertShader);
	CheckForErrors(vertShader, "Vertex");
	//Fragment 
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, nullptr);
	glCompileShader(fragShader);
	CheckForErrors(fragShader, "Fragment");
	//Geometry
	if (geomSource)
	{
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geomShader, 1, &geomSource, nullptr);
		glCompileShader(geomShader);
		CheckForErrors(geomShader,"Geometry");
	}
	//Main program
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	if (geomSource)
	{
		glAttachShader(program, geomShader);
	}
	glLinkProgram(program);
	CheckForErrors(program, "Main");
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	if (geomSource)
	{
		glDeleteShader(geomShader);
	}
}

void rb::Shader::CheckForErrors(GLuint shader, const string& shaderName)
{
	GLint success;
	GLchar errorLog[1024];
	//not the full shader program
	if (shaderName != "Main")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, errorLog);
			Debug::Error("Compile Error in " + shaderName + ": " + errorLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, errorLog);
			Debug::Error("Linker Error in " + shaderName + ": " + errorLog);
		}
	}
}
