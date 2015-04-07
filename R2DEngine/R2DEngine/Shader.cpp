#include "Shader.h"
#include <fstream>
#include <assert.h>
#include "RDebug.h"
#include "FileManager.h"

using namespace rb;

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
	glUniform1f(glGetUniformLocation(program, uniformName.c_str()), value);
}

void rb::Shader::ProcessShader(const char* vertSource, const char* fragSource, const char* geomSource /*= nullptr*/)
{
	//Debug::Log("Processing Shader: " + vertFileName);
	GLuint vertShader, fragShader, geomShader;
	
	//vertex shader
	//const char* vertSource = FileManager::ReadFile(vertFileName).c_str();
	//assert(vertSource);
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, nullptr);
	glCompileShader(vertShader);
	CheckForErrors(vertShader, "Vertex");
	//if(vertSource) delete[] vertSource;
	
	//Fragment 
	/*const char* fragSource = FileManager::ReadFile(fragFileName).c_str();
	assert(fragSource);*/
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, nullptr);
	glCompileShader(fragShader);
	CheckForErrors(fragShader, "Fragment");
	//if (fragSource) delete[] fragSource;

	//Geometry
	if (geomSource)
	{
		/*const char* geomSource = FileManager::ReadFile(geomFileName).c_str();
		assert(geomSource);*/
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geomShader, 1, &geomSource, nullptr);
		glCompileShader(geomShader);
		CheckForErrors(geomShader,"Geometry");
		//if (geomSource) delete[] geomSource;
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
