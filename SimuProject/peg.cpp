#include "peg.h"
#include "resourcebank.h"

Peg::Peg(ResourceBank& resourcebank, Vector3f& position) : 
	m_radius ( 0.1f )
{
	SetModel(resourcebank.RequestModel("Resources/peg.obj"));
	SetPosition(position);
}