#ifndef _OBJECT_H
#define _OBJECT_H

class Model;

#include "Vector3f.h"

class Object
{
private:
	Model * m_model;
	Vector3f m_position;
	float m_pitch;
	float m_yaw;
	float m_roll;

public:
	Object();
	virtual ~Object();

	void Draw();

	inline void SetModel(Model* model) { m_model = model; }
	inline void SetPosition(const Vector3f& position) { m_position = position; }

	inline void SetPitch(float pitch) { m_pitch = pitch; }
	inline void SetYaw(float yaw) { m_yaw = yaw; }
	inline void SetRoll(float roll) { m_roll = roll; }

};

#endif