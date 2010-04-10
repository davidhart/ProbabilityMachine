#ifndef _LIGHT_H
#define _LIGHT_H

class Lighting
{
public:
	static void Enable();
	static void Disable();
};

class Light
{
private:
	float m_diffuseColour[4];
	float m_specularColour[4];
	float m_ambientColour[4];

protected:
	static const int LIGHT_CHANNEL_CONSTANTS[8];

public:
	Light();
	virtual ~Light();

	static void Enable(int channel);
	static void Disable(int channel);

	void SetAmbientColour(float r, float g, float b, float a);
	void SetDiffuseColour(float r, float g, float b, float a);
	void SetSpecularColour(float r, float g, float b, float a);

	virtual void Apply(int channel);
protected:
	static bool IsChannelValid(int channel) { return (channel >= 0 && channel < 8); }
};

#endif