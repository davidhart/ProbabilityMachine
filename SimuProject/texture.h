#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "vector2f.h"

class Texture
{
protected:
	bool m_loaded;
	unsigned int m_textureID;
	Vector2f m_size;

public:
	Texture();
	virtual ~Texture();
	virtual void Load() = 0;
	void Unload();
	void Apply();
	inline const Vector2f& GetSize() { return m_size; }
};

#endif