#ifndef R_SHADER_MANAGER_H_
#define R_SHADER_MANAGER_H_

#include <unordered_map>
#include "RString.h"
#include "Shader.h"

namespace rb
{
	class ShaderManager
	{
	public:
		typedef std::unordered_map<Shader::ShaderType, Shader> ShaderTable;
		static void LoadShader(const string& vertFileName, const string& fragFileName, Shader::ShaderType type);
		static void LoadShader(const string& vertFileName, const string& fragFileName, const string& geomFileName, Shader::ShaderType type);
		static Shader GetShader(Shader::ShaderType type);

	private:
		static ShaderTable shaderTable;
	};
}
#endif // R_SHADER_MANAGER_H_
