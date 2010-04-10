#include "camera.h"
#include "Matrix3x3.h"

#include <windows.h>
#include <GL/gl.h>

#include "Math.h"

#include <iostream>

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
	Vector3f rightVector(1, 0, 0);

	Matrix3x3 rYaw;

	Matrix3x3::RotationY(rYaw, m_yaw);
	forwardVector = forwardVector * rYaw;
	rightVector = rightVector * rYaw;

	Matrix3x3 rPitch;
	Matrix3x3::RotationAxis(rPitch, rightVector, m_pitch);

	Vector3f v = forwardVector * (rPitch);
	m_position += v; 
}

void Camera::MoveStrafe(float amount)
{
	Vector3f upVector(0, 1, 0);
	Vector3f strafeVector(amount, 0, 0);

	Matrix3x3 rRoll;
	Matrix3x3::RotationZ(rRoll, m_roll);
	upVector = upVector * rRoll;
	strafeVector = strafeVector * rRoll;

	Matrix3x3 rYaw;
	Matrix3x3::RotationAxis(rYaw, upVector, m_yaw);

	Vector3f v = strafeVector * rYaw;
	m_position += v;
}

void Camera::RotatePitch(float amount)
{
	m_pitch += amount;

	// Limit angles to range between looking directly up/directly down
	// to prevent camera doing backflips/frontflips
	if ( m_pitch > MATH_PI/2 )
		m_pitch = MATH_PI/2;

	if (m_pitch < -MATH_PI/2 )
		m_pitch = -MATH_PI/2;
}

void Camera::RotateYaw(float amount)
{
	m_yaw += amount;

	// Keep the yaw between 0 and 2pi
	while (m_yaw > MATH_PI*2)
		m_yaw -= MATH_PI*2;

	while (m_yaw < 0)
		m_yaw += MATH_PI*2;
}

void Camera::RotateRoll(float amount)
{
	m_roll += amount;
}

void Camera::SetViewMatrix()
{	
	// Rotate world objects to match camera orientation
	glRotatef(m_pitch*180.0f/MATH_PI,1,0,0);
	glRotatef(m_yaw*180.0f/MATH_PI,0,1,0);
	glRotatef(m_roll*180.0f/MATH_PI,0,0,1);
	
	// Translate world away from camera
	glTranslatef(-m_position.X(), -m_position.Y(), -m_position.Z());
}
