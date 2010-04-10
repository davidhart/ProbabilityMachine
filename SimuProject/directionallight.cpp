#include "directionallight.h"

#include <windows.h>
#include <Gl/gl.h>

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(const Vector3f &direction)
{
	m_direction = direction;
	m_direction.Unit();
}

void DirectionalLight::Apply(int channel)
{
	if (IsChannelValid(channel))
	{
		Light::Apply(channel);

		GLenum channelEnum = LIGHT_CHANNEL_CONSTANTS[channel];	
		GLfloat direction[] = { m_direction.X(), m_direction.Y(), m_direction.Z(), 0.0f };

		glLightfv(channelEnum, GL_POSITION, direction);
	}
}