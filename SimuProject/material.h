#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <string>
#include "Vector3f.h"

class Texture;

class Material
{
private:
	Texture* m_texture;
	Vector3f m_ambient;
	Vector3f m_diffuse;
	Vector3f m_specular;
	float m_alpha;
	float m_shininess;
	int m_lightingMode;
public:
	Material(Texture* texture, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum);
	Material();
	~Material();

	void Apply();
	void Load();

	inline void SetTexture(Texture* texture)			{ m_texture = texture; }
	inline void SetAmbient(const Vector3f& ambient)		{ m_ambient = ambient; }
	inline void SetDiffuse(const Vector3f& diffuse)		{ m_diffuse = diffuse; }
	inline void SetSpecular(const Vector3f& specular)	{ m_specular = specular; }
	inline void SetAlpha(float alpha)					{ m_alpha = alpha; }
	inline void SetShininess(float shininess)			{ m_shininess = shininess; }
	inline void SetLightingMode(int lightingMode)		{ m_lightingMode = lightingMode; }
};

#endif