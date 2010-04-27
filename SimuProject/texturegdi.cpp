#include "texturegdi.h"
#include "timer.h"

#include <windows.h>
#include <Gl/gl.h>
#include <iostream>

TextureGdi::TextureGdi(Gdiplus::Bitmap& textureBitmap) :
	m_textureBitmap( textureBitmap )
{

}

void TextureGdi::Load()
{
	if (!m_loaded)
	{
		Gdiplus::BitmapData bitmapdata;

		Gdiplus::Rect lockRect(0, 0, m_textureBitmap.GetWidth(), m_textureBitmap.GetHeight());

		if (m_textureBitmap.LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapdata) == Gdiplus::Ok)
		{
			Timer t;
			t.Start();
	
			glPushAttrib(GL_TEXTURE_BIT);

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &m_textureID);

			glBindTexture(GL_TEXTURE_2D, m_textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureBitmap.GetWidth(), m_textureBitmap.GetHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmapdata.Scan0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_textureBitmap.UnlockBits(&bitmapdata);

			m_loaded = true;

			glPopAttrib();

			t.Stop();

			m_size.SetX(m_textureBitmap.GetWidth());
			m_size.SetY(m_textureBitmap.GetHeight());

			std::cout << "TEXTURE GDI - loaded in " << t.GetTime() << "s " << std::endl;
		}
	}
}