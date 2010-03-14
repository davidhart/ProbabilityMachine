#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <string>
#include "model.h"
#include "Vector3f.h"

class Mesh
{
private:
	std::string m_material;

	bool m_hasVn;
	bool m_hasVt;

	std::vector<float> m_packedVertices;
	std::vector<int> m_packedIndices;

	class OBJ_INDEX_CACHE
	{
	public:
		OBJ_INDEX_CACHE();
		int v,vt,vn;
		int next;
		int packedPos;
	};

public:
	Mesh(const Model::Vertex3fVector& vertices, const Model::Vertex3fVector& normals, const Model::Vertex2fVector& texCoords,
			const Model::ObjIndicesVector& indices, const std::string& material);
	virtual ~Mesh();

	void Draw();
};

#endif
