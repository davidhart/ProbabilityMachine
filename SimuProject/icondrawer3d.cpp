#include "icondrawer3d.h"

#include "camera.h"
#include "pointlight.h"
#include "texture.h"
#include "light.h"

#include <windows.h>
#include <Gl/gl.h>

#include "math.h"

IconDrawer3D::IconDrawer3D(const Camera& camera)
	: m_camera(camera)
{
}

void IconDrawer3D::Begin()
{
	glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);
	Lighting::Disable();
	glEnable(GL_TEXTURE_2D);
}

void IconDrawer3D::Draw(const PointLight &pointlight, Texture *texture)
{
	texture->Apply();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPushAttrib(GL_TEXTURE_BIT);
	glPushMatrix();

	const Vector3f& position = pointlight.GetPosition();

	glTranslatef(position.X(), position.Y(), position.Z());
	glRotatef(-m_camera.Roll()*180.0f/MATH_PI,0,0,1);
	glRotatef(-m_camera.Yaw()*180.0f/MATH_PI,0,1,0);
	glRotatef(-m_camera.Pitch()*180.0f/MATH_PI,1,0,0);

	const float* diffuseColour = pointlight.GetDiffuseColour();

	glColor3f(diffuseColour[0], diffuseColour[1], diffuseColour[2]);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);

	glEnd();	

	glPopMatrix();
	glPopAttrib();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void IconDrawer3D::End()
{
	glPopAttrib();
}