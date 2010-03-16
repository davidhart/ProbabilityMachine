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
	Material(const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum);
	Material();
	~Material();

	void Apply();
	void Load();
};

#endif