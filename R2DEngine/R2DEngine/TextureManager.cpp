#include "TextureManager.h"
#include <SOIL.h>
#include <assert.h>
#include "AssetPaths.h"
#include "RDebug.h"

using namespace rb;

rb::TextureManager::TextureTable rb::TextureManager::textureTable;

void rb::TextureManager::LoadTexture(const string& textureName, const string& textureFileName)
{
	assert(textureTable.find(textureName) == textureTable.end() && "Texture already exists in table");
	textureTable[textureName] = LoadTextureFromFile(AssetPaths::texturesPath + textureName);
}

rb::Texture rb::TextureManager::GetTexture(const string& name)
{
	assert(textureTable.find(name) != textureTable.end() && "Texture not found");
	return textureTable[name];
}
rb::Texture rb::TextureManager::LoadTextureFromFile(const string& path)
{
	Debug::Log("Loading texture from: " + path);
	Texture texture;
	int width, height;
	int channels = 0;
	unsigned char* imageData = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	texture.GenerateGLTexture(width, height, imageData);
	SOIL_free_image_data(imageData);
	return texture;
}


