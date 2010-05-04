#ifndef _FONT_H
#define _FONT_H

#include "vector2f.h"
#include <string>

#include <windows.h>
#include <gdiplus.h>
#include <vector>

class SpriteBatch;
class TextureGdi;
class Texture;

class Font
{
private:
	class Glyph
	{
	public:
		Glyph(const Vector2f& size, const Vector2f& topLeft, const Vector2f& bottomRight, Texture* texture);
		Vector2f m_size;
		Vector2f m_topLeft;
		Vector2f m_bottomRight;
		Texture* m_texture;
	};

	unsigned char m_startChar, m_endChar;
	unsigned int m_height;
	unsigned int m_spaceWidth;
	std::vector<Gdiplus::Bitmap*> m_fontMapBmps;
	std::vector<TextureGdi*> m_fontTextures;

	std::vector<Glyph*> m_glyphTable;

public:
	Font(const std::string& family, unsigned int height, bool bold, bool italic);
	~Font();
	void Load();
	void Unload();
	void DrawText(SpriteBatch& spriteBatch, const std::string& text, const Vector2f& position);
};

#endif