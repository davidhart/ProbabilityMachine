#include "texturefile.h"

#include <windows.h>
#include <Gl/gl.h>
#include "timer.h"
#include <iostream>

TextureFile::TextureFile(const std::string &filename) :
	m_filename ( std::string("Resources/") + filename ),
	m_textureData ( NULL )
{
	Timer t;
	t.Start();

	std::wstring wfilename(m_filename.begin(), m_filename.end());

	m_textureData = Gdiplus::Bitmap::FromFile(wfilename.c_str());

	t.Stop();

	if (m_textureData->GetWidth() != 0)
		std::cout << "TEXTURE (" << m_filename << ") Fetched in " << t.GetTime() << "s " << std::endl;
	else
		std::cout << "TEXTURE (" << m_filename << ") File could not be read" << std::endl;
}


TextureFile::~TextureFile()
{
	if (m_textureData != NULL)
		delete m_textureData;
}

void TextureFile::Load()
{
	if (!m_loaded)
	{
		Gdiplus::BitmapData bitmapdata;

		Gdiplus::Rect lockRect(0, 0, m_textureData->GetWidth(), m_textureData->GetHeight());

		if (m_textureData->LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapdata) == Gdiplus::Ok)
		{
			Timer t;
			t.Start();
	
			glPushAttrib(GL_TEXTURE_BIT);

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &m_textureID);

			glBindTexture(GL_TEXTURE_2D, m_textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureData->GetWidth(), m_textureData->GetHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmapdata.Scan0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_textureData->UnlockBits(&bitmapdata);

			m_loaded = true;

			glPopAttrib();

			t.Stop();

			m_size.SetX(m_textureData->GetWidth());
			m_size.SetY(m_textureData->GetHeight());

			std::cout << "TEXTURE (" << m_filename << ") loaded in " << t.GetTime() << "s " << std::endl;
		}
	}
}