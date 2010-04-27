#ifndef _TEXTUREFILE_H
#define _TEXTUREFILE_H

#include "texture.h"
#include <string>
#include <windows.h>
#include <gdiplus.h>
#include <string>

class TextureFile : public Texture
{
private:
	std::string m_filename;
	Gdiplus::Bitmap* m_textureData;
public:
	TextureFile(const std::string& filename);
	~TextureFile();

	void Load();
};

#endif