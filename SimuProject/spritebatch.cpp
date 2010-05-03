#include "spritebatch.h"

#include "texture.h"
#include "window.h"

#include <windows.h>
#include <Gl/gl.h>

SpriteBatch::Sprite::Sprite(Texture* textureHandle, const Vector2f& position, const Vector2f& size) :
	textureHandle( textureHandle ),
	position( position ),
	size( size ),
	uv1( 0,0 ),
	uv2( 1,1 )
{

}

SpriteBatch::Sprite::Sprite(Texture* textureHandle, const Vector2f& position, const Vector2f& size, 
						const Vector2f& uv1, const Vector2f& uv2) :
	textureHandle(textureHandle),
	position(position),
	size(size),
	uv1( uv1 ),
	uv2( uv2 )
{

}

SpriteBatch::SpriteBatch(const Window& window) :
	m_window ( window )
{
}

SpriteBatch::~SpriteBatch()
{
}


void SpriteBatch::Begin( )
{
	glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef (0.5f, 0.5f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w,h;
	m_window.GetSize(w,h);
	glOrtho(0, w, h, 0, -1, 1);

	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

	m_spritesToDraw.clear();
}

void SpriteBatch::Draw(Texture* t, const Vector2f& position)
{
	m_spritesToDraw.push_back(Sprite(t, position, t->GetSize()));
}

void SpriteBatch::Draw(Texture *t, const Vector2f& position, const Vector2f& uv1, const Vector2f& uv2, const Vector2f& size)
{
	m_spritesToDraw.push_back(Sprite(t, position, size, uv1, uv2));
}

void SpriteBatch::End( )
{
	unsigned int basePos = 0;

	while (basePos != m_spritesToDraw.size())
	{
		unsigned int searchPos = basePos;
		Texture* batchTexture = m_spritesToDraw[basePos].textureHandle;

		while (searchPos < m_spritesToDraw.size()-1 && m_spritesToDraw[searchPos+1].textureHandle == batchTexture)
		{
			searchPos++;
		}

		batchTexture->Apply();

		glBegin(GL_QUADS);

		for (unsigned int i = basePos; i <= searchPos; i++)
		{
			glTexCoord2f(m_spritesToDraw[i].uv1.X(), m_spritesToDraw[i].uv1.Y());
			glVertex2f(m_spritesToDraw[i].position.X(), m_spritesToDraw[i].position.Y());

			glTexCoord2f(m_spritesToDraw[i].uv1.X(), m_spritesToDraw[i].uv2.Y());
			glVertex2f(m_spritesToDraw[i].position.X(), m_spritesToDraw[i].position.Y()+m_spritesToDraw[i].size.Y());

			glTexCoord2f(m_spritesToDraw[i].uv2.X(), m_spritesToDraw[i].uv2.Y());
			glVertex2f(m_spritesToDraw[i].position.X()+m_spritesToDraw[i].size.X(), m_spritesToDraw[i].position.Y()+m_spritesToDraw[i].size.Y());

			glTexCoord2f(m_spritesToDraw[i].uv2.X(), m_spritesToDraw[i].uv1.Y());
			glVertex2f(m_spritesToDraw[i].position.X()+m_spritesToDraw[i].size.X(), m_spritesToDraw[i].position.Y());
		}

		glEnd();

		basePos = searchPos+1;		
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();
}