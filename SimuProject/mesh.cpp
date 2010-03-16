#include "mesh.h"

#include <windows.h>
#include <Gl/gl.h>

Mesh::OBJ_INDEX_CACHE::OBJ_INDEX_CACHE() : 
	next ( -1 ),
	packedPos ( -1 )
{

}

Mesh::Mesh(const Model::Vertex3fVector& vertices, const Model::Vertex3fVector& normals, const Model::Vertex2fVector& texCoords,
		   const Model::ObjIndicesVector& indices, Material* material) :
	m_material(material)
{

	m_hasVt = indices[0].hasVt;
	m_hasVn = indices[0].hasVn;

	int stride = 3;
	if (m_hasVt)
		stride += 2;

	if (m_hasVn)
		stride += 3;

	std::vector<OBJ_INDEX_CACHE> packedIndicesCache(vertices.size());

	for (unsigned int i = 0; i < indices.size(); i++)
	{
		// not yet packed
		int v = indices[i].v-1;
		if (packedIndicesCache[v].packedPos == -1)
		{
			m_packedVertices.push_back(vertices[indices[i].v-1].X());
			m_packedVertices.push_back(vertices[indices[i].v-1].Y());
			m_packedVertices.push_back(vertices[indices[i].v-1].Z());
			packedIndicesCache[v].v = indices[i].v;

			if (m_hasVt)
			{
				m_packedVertices.push_back(texCoords[indices[i].vt-1].X());
				m_packedVertices.push_back(texCoords[indices[i].vt-1].Y());
				packedIndicesCache[v].vt = indices[i].vt;

			}

			if (m_hasVn)
			{
				m_packedVertices.push_back(normals[indices[i].vn-1].X());
				m_packedVertices.push_back(normals[indices[i].vn-1].Y());
				m_packedVertices.push_back(normals[indices[i].vn-1].Z());
				packedIndicesCache[v].vn = indices[i].vn;
			}

			m_packedIndices.push_back((m_packedVertices.size()/stride)-1);

			packedIndicesCache[v].packedPos = (m_packedVertices.size()/stride)-1;
		}
		// otherwise search cache
		else
		{
			bool found = false;

			int index = indices[i].v-1;
			while (!found)
			{
				if (((!m_hasVn) || (m_hasVn && packedIndicesCache[index].vn == indices[i].vn)) && 
					((!m_hasVt) || (m_hasVt && packedIndicesCache[index].vt == indices[i].vt)))
				{

					m_packedIndices.push_back(packedIndicesCache[index].packedPos);
					found = true;
					break;
				}
				else
				{
					if (packedIndicesCache[index].next == -1)
						break;
					else
						index = packedIndicesCache[index].next;
				}
			}

			if (!found)
			{
				packedIndicesCache.push_back(OBJ_INDEX_CACHE());

				m_packedVertices.push_back(vertices[indices[i].v-1].X());
				m_packedVertices.push_back(vertices[indices[i].v-1].Y());
				m_packedVertices.push_back(vertices[indices[i].v-1].Z());
				packedIndicesCache.back().v = indices[i].v;

				if (m_hasVt)
				{
					m_packedVertices.push_back(texCoords[indices[i].vt-1].X());
					m_packedVertices.push_back(texCoords[indices[i].vt-1].Y());
					packedIndicesCache.back().vt = indices[i].vt;

				}

				if (m_hasVn)
				{
					m_packedVertices.push_back(normals[indices[i].vn-1].X());
					m_packedVertices.push_back(normals[indices[i].vn-1].Y());
					m_packedVertices.push_back(normals[indices[i].vn-1].Z());
					packedIndicesCache.back().vn = indices[i].vn;
				}

				m_packedIndices.push_back((m_packedVertices.size()/stride)-1);

				packedIndicesCache[index].next = packedIndicesCache.size()-1;
				packedIndicesCache.back().packedPos = (m_packedVertices.size()/stride)-1;
			}
		}
	}
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{	
	m_material->Apply();

	int stride = 3*sizeof(float);

	if (m_hasVt)
		stride+=2*sizeof(float);

	if (m_hasVn)
		stride += 3*sizeof(float);

	glEnableClientState(GL_VERTEX_ARRAY);
	
	if (m_hasVt)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (m_hasVn)
		glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, stride,  &m_packedVertices[0]);
	
	if (m_hasVt)
	{
		glTexCoordPointer(2, GL_FLOAT, stride, &m_packedVertices[3]); 
	}

	if (m_hasVn)
	{
		int vnOffs = m_hasVt ? 5 : 3;
		glNormalPointer(GL_FLOAT, stride, &m_packedVertices[vnOffs]);
	}
	glDrawElements(GL_TRIANGLES, m_packedIndices.size(), GL_UNSIGNED_INT, &m_packedIndices[0]); 

	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_hasVt)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (m_hasVn)
		glDisableClientState(GL_NORMAL_ARRAY);

}