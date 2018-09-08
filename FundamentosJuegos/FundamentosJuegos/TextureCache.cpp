#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath) {
	auto mit = textureMap.find(texturePath);
	if (mit == textureMap.end()) {
		GLTexture texture = ImageLoader::loadPNG(texturePath);
		textureMap[texturePath] = texture;
		return texture;
	}
	return mit->second;
}

TextureCache::~TextureCache()
{
}