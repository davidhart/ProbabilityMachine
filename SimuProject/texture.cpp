#include "texture.h"
#include "timer.h"

#include <iostream>

#include <windows.h>
#include <Gl/gl.h>

Texture::Texture() :
	m_loaded( 0 ),
	m_textureID( 0 )
{

}

Texture::~Texture()
{
	Unload();
}

void Texture::Unload()
{
	if (m_loaded)
	{
		glDeleteTextures(1, &m_textureID);
		m_loaded = false;
	}
}

void Texture::Apply()
{
	if (m_loaded)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}