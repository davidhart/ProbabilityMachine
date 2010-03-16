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
}

Texture::~Texture()
{
	if (m_loaded)
	{
		glDeleteTextures(1, &m_textureID);
		delete m_textureData;
	}
}

void Texture::Load()
{
	Timer t;
	t.Start();

	std::wstring wfilename(m_filename.begin(), m_filename.end());

	m_textureData = Gdiplus::Bitmap::FromFile(wfilename.c_str());

	Gdiplus::BitmapData bitmapdata;

	Gdiplus::Rect lockRect(0, 0, m_textureData->GetWidth(), m_textureData->GetHeight());

	if (m_textureData->LockBits(&lockRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapdata) == Gdiplus::Ok)
	{

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_textureID);

		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureData->GetWidth(), m_textureData->GetHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmapdata.Scan0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		m_textureData->UnlockBits(&bitmapdata);

		m_loaded = true;

		t.Stop();
		std::cout << "TEXTURE (" << m_filename << ") loaded in " << t.GetTime() << "s " << std::endl;

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		delete m_textureData;
		std::cout << "Error couldn't load " << m_filename << std::endl; 

	}
}

void Texture::Apply()
{
	if (m_loaded)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}