#ifndef R_SHADER_H_
#define R_SHADER_H_

#include "GL_Includes.h"
#include "RString.h"
#include "RVector.h"
#include "RMatrix.h"

namespace rb
{
	class Shader
	{
	public:
		enum class ShaderType { SpriteShader, PointSprite, AnimatedSprite };

		const static string& modelUniformName;
		const static string& projUniformName;
		const static string& spriteTextureName;
		const static string& spriteColourName;

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
		void SetInt(const string& uniforName, int value);
		void SetVec3(const string& uniformName, const Vec3& value);
		void SetVec4(const string& uniformName, const Vec4& value);
		void SetMat4(const string& uniformName, const Mat4& value);

	private:
		//Fields
		ShaderType type;
		GLuint program;

		//Methods
		GLint GetUniformLoc(const string& uniformName);
		void ProcessShader(const char* vertSource, const char* fragSource, const char* geomSource = nullptr);
		void CheckForErrors(GLuint shader, const string& shaderName);
	};

}

#endif // R_SHADER_H_
