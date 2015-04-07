#ifndef R_TEXTURE_MANAGER_H_
#define R_TEXTURE_MANAGER_H_

#include <map>
#include "RString.h"
#include "Texture.h"

namespace rb
{
	class TextureManager
	{
	public:
		typedef std::map<string, Texture> TextureTable;
		static void LoadTexture(const string& textureName, const string& textureFileName);
		static Texture GetTexture(const string& name);
	private:
		static TextureTable textureTable;
		static Texture LoadTextureFromFile(const string& path);
	};
}

#endif // R_TEXTURE_MANAGER_H_
