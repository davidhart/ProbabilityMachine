#include "pointlight.h"
#include "texture.h"

#include <windows.h>
#include <Gl/gl.h>

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

void PointLight::SetPosition(const Vector3f& position)
{
	m_position = position;
}

void PointLight::Apply(int channel)
{
	if (IsChannelValid(channel))
	{
		Light::Apply(channel);

		GLenum channelEnum = LIGHT_CHANNEL_CONSTANTS[channel];

		GLfloat pos[] = { m_position.X(), m_position.Y(), m_position.Z(), 1.0f };
		glLightfv(channelEnum, GL_POSITION, pos);
	}
}