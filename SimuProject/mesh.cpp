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
	m_material ( material ),
	m_loaded ( false ),
	m_displayListID ( 0 )
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

			int packedPos = (m_packedVertices.size()/stride)-1;

			m_packedIndices.push_back(packedPos);
			packedIndicesCache[v].packedPos = packedPos;
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

				int packedPos = (m_packedVertices.size()/stride)-1;

				m_packedIndices.push_back(packedPos);
				packedIndicesCache[index].next = packedIndicesCache.size()-1;
				packedIndicesCache.back().packedPos = packedPos;
			}
		}
	}
}

Mesh::~Mesh()
{
	Unload();
}

void Mesh::Draw()
{	
	if ( m_loaded )
	{
		m_material->Apply();

		glCallList(m_displayListID);
	}
}

void Mesh::Load()
{
	if (!m_loaded)
	{
		m_displayListID = glGenLists(1);

		if (m_displayListID != 0)
		{
			glNewList(m_displayListID, GL_COMPILE);

			int stride = 3*sizeof(float);

			if (m_hasVt) stride += 2 * sizeof(float);
			if (m_hasVn) stride += 3 * sizeof(float);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, stride,  &m_packedVertices[0]);

			if (m_hasVt)
			{
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, stride, &m_packedVertices[3]); 
			}

			if (m_hasVn)
			{
				glEnableClientState(GL_NORMAL_ARRAY);
				int vnOffs = m_hasVt ? 5 : 3;
				glNormalPointer(GL_FLOAT, stride, &m_packedVertices[vnOffs]);
			}

			glDrawElements(GL_TRIANGLES, m_packedIndices.size(), GL_UNSIGNED_INT, &m_packedIndices[0]); 

			glDisableClientState(GL_VERTEX_ARRAY);

			if (m_hasVt) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			if (m_hasVn) glDisableClientState(GL_NORMAL_ARRAY);

			glEndList();
	
			m_loaded = true;
		}
	}
}

void Mesh::Unload()
{
	if (m_loaded)
	{
		glDeleteLists(m_displayListID, 1);

		m_loaded = false;
	}
}

unsigned int Mesh::GetTriCount()
{
	return m_packedIndices.size()/3;
}