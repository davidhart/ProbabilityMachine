#ifndef _PEG_H
#define _PEG_H

#include "physicsobject.h"

class ResourceBank;

class Peg : public PhysicsObject
{
private:
	float m_radius;

public:
	Peg(ResourceBank& resourcebank, const Vector3f& position);
	inline float GetRadius() const { return m_radius; }
};

#endif