#include "object.h"
#include "model.h"

#include <windows.h>
#include <Gl/gl.h>

Object::Object(Model *model, const Vector3f &position) : 
	m_model ( model ),
	m_position ( position ),
	m_pitch ( 0.0f ),
	m_yaw ( 0.0f ),
	m_roll ( 0.0f )
{
}

Object::~Object()
{
}

void Object::Draw()
{
	glPushMatrix();
	glRotatef(m_roll, 0, 0, 1);
	glRotatef(m_yaw, 0, 1, 0);
	glRotatef(m_pitch, 1, 0, 0);

	glTranslatef(m_position.X(), m_position.Y(), m_position.Z());

	m_model->Draw();

	glPopMatrix();
}
