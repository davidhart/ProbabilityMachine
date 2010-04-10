#include "texture.h"
#include "timer.h"

#include <Gl/gl.h>

#include <iostream>

Texture::Texture(const std::string &filename) :
	m_filename ( std::string("Resources/") + filename ),
	m_textureData ( NULL ),
	m_loaded ( false ),
	m_textureID ( 0 )
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

Texture::~Texture()
{
	Unload();
}

void Texture::Load()
{
	if (!m_loaded)
	{
		Gdiplus::BitmapData bitmapdata;

		Gdiplus::Rect lockRect(0, 0, m_textureData->GetWidth(), m_textureData->GetHeight());

		if (m_textureData->LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapdata) == Gdiplus::Ok)
		{
			Timer t;
			t.Start();
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &m_textureID);

			glBindTexture(GL_TEXTURE_2D, m_textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureData->GetWidth(), m_textureData->GetHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmapdata.Scan0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_textureData->UnlockBits(&bitmapdata);

			m_loaded = true;

			glDisable(GL_TEXTURE_2D);

			t.Stop();

			std::cout << "TEXTURE (" << m_filename << ") loaded in " << t.GetTime() << "s " << std::endl;
		}
	}
}

void Texture::Unload()
{
	if (m_loaded)
	{
		glDeleteTextures(1, &m_textureID);
		m_loaded = false;
	}

	delete m_textureData;
}

void Texture::Apply()
{
	if (m_loaded)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}