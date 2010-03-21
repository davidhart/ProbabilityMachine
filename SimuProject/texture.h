#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <windows.h>
#include <gdiplus.h>
#include <string>

class Texture
{
private:
	std::string m_filename;
	Gdiplus::Bitmap* m_textureData;

	unsigned int m_textureID;
	bool m_loaded;

public:
	Texture(const std::string& filename);
	~Texture();
	void Load();
	void Unload();
	void Apply();
};

#endif