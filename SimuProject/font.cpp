#include "font.h"

#include "texture.h"
#include "texturegdi.h"

#include <cmath>
#include "spritebatch.h"

Font::Glyph::Glyph(const Vector2f& size, const Vector2f& topLeft, const Vector2f& bottomRight, Texture* texture) :
	m_size(size),
	m_topLeft(topLeft),
	m_bottomRight(bottomRight),
	m_texture(texture)
{

}

Font::Font(const std::string& family, unsigned int height, bool bold, bool italic) :
	m_startChar(33),
	m_endChar(255),
	m_height(height),
	m_spaceWidth(0)
{
	
	// family name to wstring
	std::wstring wfamily(family.length(), L' ');
	std::copy(family.begin(), family.end(), wfamily.begin());

	Gdiplus::Font font(wfamily.c_str(), (Gdiplus::REAL)height, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	const Gdiplus::StringFormat * sf = Gdiplus::StringFormat::GenericTypographic();

	int i = 0;
	
	while (i <= m_endChar-m_startChar)
	{
		// Make texture and bitmap to fill with letters
		Gdiplus::Bitmap* fontMapBmp = new Gdiplus::Bitmap(512,512, PixelFormat32bppARGB);
		m_fontMapBmps.push_back(fontMapBmp);
		TextureGdi* fontTexture = new TextureGdi(*fontMapBmp);
		m_fontTextures.push_back(fontTexture);

		// Gdi rendering context
		Gdiplus::Graphics graphics(fontMapBmp);
		graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

		// Calculate the width of a space character, since GDI returns 0 width for a " " string
		Gdiplus::RectF boundingBox;
		graphics.MeasureString(L"O", 1, &font, Gdiplus::PointF(0, 0), sf, &boundingBox);
		Gdiplus::RectF boundingBoxSpace;
		graphics.MeasureString(L"O O", 3, &font, Gdiplus::PointF(0, 0), sf, &boundingBoxSpace);
		m_spaceWidth = (unsigned int)(boundingBoxSpace.Width - boundingBox.Width*2);

		// Hack to add extra paddding to prevent overlap problem
		float padding = m_spaceWidth/2.0f; 

		float x = 0.0f, y = 0.0f;
		float lineheight = 0.0f;

		for (; i <= m_endChar-m_startChar; i++)
		{
			// Iteration# to ascii character, character to wide-char
			char letter = (CHAR)(i+m_startChar);
			WCHAR wcharletter;
			MultiByteToWideChar(CP_ACP, 0, &letter, 1, &wcharletter, 1);

			graphics.MeasureString(&wcharletter, 1, &font, Gdiplus::PointF(0, 0), sf, &boundingBox);

			// Is it the tallest in this row?
			if (boundingBox.Height>lineheight)
				lineheight = boundingBox.Height;

			// Will it fit on this row?
			if(x+boundingBox.Width+padding >= 512)
			{
				x=0;
				y+= ceilf(lineheight+padding);
				lineheight = 0.0f;
			}

			// Will it fit on this texture?
			if (y + boundingBox.Height+padding >= 512)
				break;

			// Draw onto bitmap
			graphics.DrawString(&wcharletter, 1, &font, Gdiplus::PointF(x, y), sf, &brush);

			// Record position, size, texture of this letter
			Vector2f size(ceilf(boundingBox.Width), ceilf(boundingBox.Height));
			Vector2f uv1((x+0.5f)/512.0f,(y+0.5f)/512.0f);
			Vector2f uv2((x+size.X()+0.5f)/512.0f,(y+size.Y()+0.5f)/512.0f);
			m_glyphTable.push_back(new Glyph(size, uv1, uv2, fontTexture));

			x+= ceilf(boundingBox.Width+padding);
		}
	}
}

Font::~Font()
{
	std::vector<Glyph*>::iterator iG = m_glyphTable.begin();
	while (iG != m_glyphTable.end())
	{
		delete *iG;
		iG++;
	}

	std::vector<TextureGdi*>::iterator iT = m_fontTextures.begin();
	while (iT != m_fontTextures.end())
	{
		delete *iT;
		iT++;
	}

	std::vector<Gdiplus::Bitmap*>::iterator iB = m_fontMapBmps.begin();
	while (iB != m_fontMapBmps.end())
	{
		delete *iB;
		iB++;
	}
}

void Font::Load()
{
	std::vector<TextureGdi*>::iterator iT = m_fontTextures.begin();
	while (iT != m_fontTextures.end())
	{
		(*iT)->Load();
		iT++;
	}
}

void Font::Unload()
{
	std::vector<TextureGdi*>::iterator iT = m_fontTextures.begin();
	while (iT != m_fontTextures.end())
	{
		(*iT)->Unload();
		iT++;
	}
}

void Font::DrawText(SpriteBatch& spriteBatch, const std::string& text, Vector2f& position)
{
	Vector2f currentPosition = position;

	for(unsigned int i = 0; i < text.size(); i++)
	{
		unsigned char letter = text[i];

		if (letter == '\n')
		{
			currentPosition.SetX(position.X());
			currentPosition.SetY(currentPosition.Y() + m_height);
		}
		else if (letter == ' ')
		{
			currentPosition.SetX(currentPosition.X() + m_spaceWidth);
		}
		else if (letter >= m_startChar && letter <= m_endChar)
		{
			Glyph* g = m_glyphTable[letter-m_startChar];
			spriteBatch.Draw(g->m_texture, currentPosition, g->m_topLeft,
				g->m_bottomRight, g->m_size);

			currentPosition.SetX(currentPosition.X() + g->m_size.X());
		}
	}
}
