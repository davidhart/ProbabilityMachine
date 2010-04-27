#ifndef _SPRITEBATCH_H
#define _SPRITEBATCH_H


#include <vector>
#include "vector2f.h"
class Texture;
class Window;

class SpriteBatch
{
private:
	struct Sprite
	{
		Sprite(Texture* textureHandle, const Vector2f& position, const Vector2f& size);
		Sprite(Texture* textureHandle, const Vector2f& position, const Vector2f& size, 
			const Vector2f& uv1, const Vector2f& uv2);
		Texture* textureHandle;
		Vector2f position;
		Vector2f size;
		Vector2f uv1;
		Vector2f uv2;
	};
	std::vector<Sprite> m_spritesToDraw;
	const Window& m_window;

public:
	SpriteBatch(const Window& window);
	~SpriteBatch();

	void Begin( );
	void Draw(Texture *t, const Vector2f& position, const Vector2f& uv1, const Vector2f& uv2, const Vector2f& size);
	void Draw(Texture*t, const Vector2f& position);
	void End( );

private:

};

#endif