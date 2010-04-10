#include "light.h"

#include <windows.h>
#include <Gl/gl.h>

void Lighting::Enable()
{
	glEnable(GL_LIGHTING);
}

void Lighting::Disable()
{
	glDisable(GL_LIGHTING);
}

const int Light::LIGHT_CHANNEL_CONSTANTS[8] = 
{
	GL_LIGHT0,
	GL_LIGHT1,
	GL_LIGHT2,
	GL_LIGHT3,
	GL_LIGHT4,
	GL_LIGHT5,
	GL_LIGHT6,
	GL_LIGHT7,
};

Light::Light() 
{
	m_ambientColour[0] = 0.0f;
	m_ambientColour[1] = 0.0f;
	m_ambientColour[2] = 0.0f;
	m_ambientColour[3] = 1.0f;

	m_diffuseColour[0] = 0.0f;
	m_diffuseColour[1] = 0.0f;
	m_diffuseColour[2] = 0.0f;
	m_diffuseColour[3] = 1.0f;

	m_specularColour[0] = 0.0f;
	m_specularColour[1] = 0.0f;
	m_specularColour[2] = 0.0f;
	m_specularColour[3] = 1.0f;
}

Light::~Light()
{
}

void Light::Enable(int channel)
{
	if (IsChannelValid(channel))
	{
		glEnable(LIGHT_CHANNEL_CONSTANTS[channel]);		
	}
}

void Light::Disable(int channel)
{
	if(IsChannelValid(channel))
	{
		glDisable(LIGHT_CHANNEL_CONSTANTS[channel]);
	}
}

void Light::SetAmbientColour(float r, float g, float b, float a)
{
	m_ambientColour[0] = r;
	m_ambientColour[1] = g;
	m_ambientColour[2] = b;
	m_ambientColour[3] = a;
}

void Light::SetDiffuseColour(float r, float g, float b, float a)
{
	m_diffuseColour[0] = r;
	m_diffuseColour[1] = g;
	m_diffuseColour[2] = b;
	m_diffuseColour[3] = a;
}

void Light::SetSpecularColour(float r, float g, float b, float a)
{
	m_specularColour[0] = r;
	m_specularColour[1] = g;
	m_specularColour[2] = b;
	m_specularColour[3] = a;
}

void Light::Apply(int channel)
{
	if (IsChannelValid(channel))
	{
		GLenum channelEnum = LIGHT_CHANNEL_CONSTANTS[channel];
		glLightfv(channelEnum, GL_AMBIENT, m_ambientColour);
		glLightfv(channelEnum, GL_DIFFUSE, m_diffuseColour);
		glLightfv(channelEnum, GL_SPECULAR, m_specularColour);
	}
}