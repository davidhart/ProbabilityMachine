#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector3f.h"

class Camera
{
private:
	Vector3f m_position;

	float m_pitch;
	float m_yaw;
	float m_roll;

public:
	Camera(const Vector3f& position, float pitch, float yaw, float roll);

	inline const Vector3f& Position() { return m_position; }
	inline void Position(const Vector3f& position) { m_position = position; }

	inline float Pitch() const { return m_pitch; }
	inline void Pitch(float pitch) { m_pitch = pitch; }

	inline float Yaw() const { return m_yaw; }
	//inline void Yaw(float yaw) { m_yaw = yaw; }

	inline float Roll() const { return m_roll; }
	//inline void Roll(float roll) { m_roll = roll; }

	void MoveForward(float amount);
	void MoveStrafe(float amount);

	void RotatePitch(float amount);
	void RotateYaw(float amount);
	void RotateRoll(float amount);

	void SetViewMatrix();

};

#endif