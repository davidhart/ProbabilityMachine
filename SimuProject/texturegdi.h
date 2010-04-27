#ifndef _TEXTUREGDI_H
#define _TEXTUREGDI_H

#include <windows.h>
#include <Gdiplus.h>
#include "texture.h"

class TextureGdi : public Texture
{
private:
	Gdiplus::Bitmap& m_textureBitmap;

	const TextureGdi& operator=(TextureGdi&);
public:
	TextureGdi(Gdiplus::Bitmap& textureBitmap);

	void Load();
	void Apply();

};

#endif