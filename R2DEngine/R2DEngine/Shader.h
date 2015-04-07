#ifndef R_SHADER_H_
#define R_SHADER_H_

#include "GL_Includes.h"
#include "RString.h"

namespace rb
{
	class Shader
	{
	public:
		enum class ShaderType { SpriteShader };
		//ctors
		Shader() = default;
		Shader(const string& vertexFileName, const string& fragmentFileName, ShaderType type);
		Shader(const string& vertexFileName, const string& fragmentFileName, const string& geometryFileName, ShaderType type);

		//Getters/setters
		GLuint Program() const;
		ShaderType Type() const;
		
		//shader interface
		void Use() const;
		static void Unbind();
		void SetFloat(const string& uniformName, float value);

	private:
		//Fields
		ShaderType type;
		GLuint program;

		//Methods
		void ProcessShader(const char* vertSource, const char* fragSource, const char* geomSource = nullptr);
		void CheckForErrors(GLuint shader, const string& shaderName);
	};

}

#endif // R_SHADER_H_
