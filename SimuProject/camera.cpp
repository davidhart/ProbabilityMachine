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

	Matrix3x3 rX, rY, rZ;

	Matrix3x3::RotationX(rX, m_pitch);
	Matrix3x3::RotationY(rY, m_yaw);
	Matrix3x3::RotationY(rZ, m_roll);

	Vector3f v = forwardVector * (rY * rX);
	m_position = m_position.Add(v); 


	std::cout << "A: " << m_pitch << " " << m_yaw << " " << m_roll << std::endl;
	std::cout << "v: " << v.X() << " " << v.Y() << " " << v.Z() << std::endl;

}

void Camera::MoveStrafe(float amount)
{
	Vector3f strafeVector(amount, 0, 0);

	Matrix3x3 rX, rY, rZ;

	Matrix3x3::RotationX(rX, m_pitch);
	Matrix3x3::RotationY(rY, m_yaw);
	Matrix3x3::RotationZ(rZ, m_roll);
	
	m_position = m_position.Add(((strafeVector * rZ) * rY) * rX); 
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
	glRotatef(m_pitch*180/MATH_PI,1,0,0);
	glRotatef(m_yaw*180/MATH_PI,0,1,0);
	glRotatef(m_roll*180/MATH_PI,0,0,1);
	
	glTranslatef(-m_position.X(), -m_position.Y(), -m_position.Z());
}
