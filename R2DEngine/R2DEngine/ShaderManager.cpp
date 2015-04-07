#include "ShaderManager.h"
#include <assert.h>
#include "RDebug.h"
#include "FileManager.h"

using namespace rb;

rb::ShaderManager::ShaderTable rb::ShaderManager::shaderTable;

rb::Shader rb::ShaderManager::GetShader(Shader::ShaderType type)
{
	assert(shaderTable.find(type) != shaderTable.end() && "Shader not found");
	return shaderTable[type];
}

void rb::ShaderManager::LoadShader(const string& vertFileName, const string& fragFileName, Shader::ShaderType type)
{
	LoadShader(vertFileName, fragFileName, "", type);
}

void rb::ShaderManager::LoadShader(const string& vertFileName, const string& fragFileName, const string& geomFileName, Shader::ShaderType type)
{
	assert(shaderTable.find(type) == shaderTable.end() && "Shader already exists");
	Debug::Log("Loading shader: " + vertFileName);
	shaderTable[type] = Shader(
		FileManager::ReadFile(vertFileName), 
		FileManager::ReadFile(fragFileName),
		geomFileName.empty()? "" : FileManager::ReadFile(geomFileName), 
		type);
}
