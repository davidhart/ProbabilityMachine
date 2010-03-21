#include "object.h"
#include "model.h"

#include <windows.h>
#include <Gl/gl.h>

Object::Object() : 
	m_model ( NULL ),
	m_position ( 0, 0, 0 ),
	m_pitch ( 0 ),
	m_yaw ( 0 ),
	m_roll ( 0 )
{
}

Object::~Object()
{
}

void Object::Draw()
{
	if (m_model != NULL)
	{
		glPushMatrix();
		glRotatef(m_roll, 0, 0, 1);
		glRotatef(m_yaw, 0, 1, 0);
		glRotatef(m_pitch, 1, 0, 0);

		glTranslatef(m_position.X(), m_position.Y(), m_position.Z());

		m_model->Draw();

		glPopMatrix();
	}
}
