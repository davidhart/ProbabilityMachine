#include "camera.h"

#include <windows.h>
#include <GL/gl.h>

Camera::Camera(const Vector3f &position, float pitch, float yaw, float roll) :
	m_position(position),
	m_pitch(pitch),
	m_yaw(yaw),
	m_roll(roll)
{
}



void Camera::MoveForward(float amount)
{
	Vector3f forwardVector(0, 0, amount);

	// TODO: need a matrix class

	// rotate vector by roll/yaw/pitch
	
	m_position = m_position.Add(forwardVector); 
}

void Camera::MoveStrafe(float amount)
{
	Vector3f strafeVector(amount, 0, 0);

	// TODO: need a matrix class

	// rotate vector by roll/yaw/pitch

	m_position = m_position.Add(strafeVector);
}

void Camera::RotatePitch(float amount)
{
	m_pitch += amount;
}

void Camera::RotateYaw(float amount)
{
	m_yaw += amount;
}

void Camera::RotateRoll(float amount)
{
	m_roll += amount;
}

void Camera::SetViewMatrix()
{
	glRotatef(m_roll,0,0,1);
	glRotatef(m_yaw,0,1,0);
	glRotatef(m_pitch,1,0,0);

	glTranslatef(m_position.X(), m_position.Y(), m_position.Z());
}
