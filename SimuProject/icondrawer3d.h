#ifndef _ICONDRAWER3D_H
#define _ICONDRAWER3D_H

class PointLight;
class Camera;
class Vector3f;
class Texture;


class IconDrawer3D
{
private:
	const Camera& m_camera;

public:
	IconDrawer3D(const Camera& camera);
	void Begin();
	void Draw(const PointLight& pointlight, Texture* texture);
	void Draw(const Vector3f& position, Texture* texture);
	void End();

private:
	
	void Draw(const Vector3f& position, Texture* texture, const float * colour);
	const IconDrawer3D& operator=(const IconDrawer3D& rhs);
};

#endif