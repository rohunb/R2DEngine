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
	Debug::Log("Loading texture \"" + textureName + "\" from: " + AssetPaths::spritesPath + textureFileName);
	textureTable[textureName] = LoadTextureFromFile(AssetPaths::spritesPath + textureFileName);
}

rb::Texture rb::TextureManager::GetTexture(const string& name)
{
	assert(textureTable.find(name) != textureTable.end() && "Texture not found");
	return textureTable[name];
}
rb::Texture rb::TextureManager::LoadTextureFromFile(const string& path)
{
	Texture texture;
	int width, height;
	int channels = 0;
	unsigned char* imageData = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	if (!imageData) Debug::Error("SOIL could not load " + path + " Error: "+SOIL_last_result());
	assert(imageData);
	texture.GenerateGLTexture(width, height, imageData);
	SOIL_free_image_data(imageData);
	return texture;
}


