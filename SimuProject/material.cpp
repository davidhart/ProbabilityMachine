#include "material.h"

#include "texture.h"

#include <Gl/gl.h>

Material::Material(const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum) :
		m_ambient(Ka),
		m_diffuse(Kd),
		m_specular(Ks),
		m_alpha(d),
		m_shininess(Ns),
		m_lightingMode(illum)
{
	if (!kdMap.empty())
		m_texture = new Texture(kdMap);
	else
		m_texture = NULL;

}

Material::Material() :
	m_texture(NULL),
	m_ambient(0.2f, 0.2f, 0.2f),
	m_diffuse(0.8f, 0.8f, 0.8f),
	m_specular(1.0f, 1.0f, 1.0f),
	m_alpha(1.0f),
	m_shininess(0.0f),
	m_lightingMode(1)
{
	
}

Material::~Material()
{
}

void Material::Apply()
{
	if (m_texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		m_texture->Apply();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	GLfloat temp[4];
	temp[0] = m_ambient.X();
	temp[1] = m_ambient.Y();
	temp[2] = m_ambient.Z();
	temp[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, temp);

	temp[0] = m_diffuse.X();
	temp[1] = m_diffuse.Y();
	temp[2] = m_diffuse.Z();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, temp);

	if (m_lightingMode == 1)
	{
		glMaterialf(GL_FRONT, GL_SHININESS, 0);

		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		glMaterialfv(GL_FRONT, GL_SPECULAR, temp);
	}
	else if (m_lightingMode == 2)
	{
		glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);

		temp[0] = m_specular.X();
		temp[1] = m_specular.Y();
		temp[2] = m_specular.Z();
		glMaterialfv(GL_FRONT, GL_SPECULAR, temp);
	}
}

void Material::Load()
{
	if (m_texture != NULL)
		m_texture->Load();
}