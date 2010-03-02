#include "model.h"
#include "mesh.h"

#include "timer.h"

#include <windows.h>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

#include <GL/gl.h>

Model::OBJ_FORMAT_INDEX::OBJ_FORMAT_INDEX(int v, int vn, int vt) :
	v ( v ),
	vn ( vn ),
	vt ( vt ),
	hasVn( true ),
	hasVt( true )
{
}

Model::OBJ_FORMAT_INDEX::OBJ_FORMAT_INDEX(int v) :
	v ( v ),
	hasVn ( false ),
	hasVt ( false )
{
}

void Model::OBJ_FORMAT_INDEX::SetVn(int vn)
{
	this->vn = vn;
	hasVn = true;
}

void Model::OBJ_FORMAT_INDEX::SetVt(int vt)
{
	this->vt = vt;
	hasVt = true;
}

Model::OBJ_INDEX_CACHE::OBJ_INDEX_CACHE() : 
	next ( -1 ),
	packedPos ( -1 )
{

}

Model::Model(const std::string& filename) :
	m_filename ( filename )
{
	int i;
	for (i = filename.length()-1; i >= 0; i--)
	{
		if (filename[i] == '.')
			break;
	}

	std::ifstream file(filename.c_str());

	// if the file could be opened
	if(file.good())
	{
		// parse extension
		if (i >= 0 && i != (signed)filename.length()-1)
		{
			std::string extension = filename.substr(i+1);
			std::transform(extension.begin(), extension.end(), extension.begin(), tolower);
		
			if (extension == "obj")
			{
				LoadFromOBJFile(file);
			}
			else if (extension == "md2")
			{
				LoadFromMD2File(file);
			}
		}

		file.close();
	}
}

Model::~Model()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];
}

void Model::LoadFromOBJFile(std::ifstream& file)
{
	Timer t;
	t.Start();
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> vertNormals;
	std::vector<Vector2f> vertTextureCoords;
	std::vector<OBJ_FORMAT_INDEX> indices;
	
	std::string token;
	
	/*
	int vCount = 0, vnCount = 0, vtCount = 0;
	
	while (!file.eof())
	{
		file >> token;

		if (token == "v")
			vCount++;
		else if (token == "vn")
			vnCount++;
		else if (token == "vt")
			vtCount++;

		file.ignore(1000, '\n');
	}

	vertices.reserve(vCount);
	vertNormals.reserve(vnCount);
	vertTextureCoords.reserve(vtCount);

	file.clear();
	file.seekg(std::ios_base::beg);
	*/

	Timer tRead;
	tRead.Start();

	bool errorEncountered = false;

	while(!file.eof())
	{
		file>>token;

		if (!file.fail())
		{
		if (token == "v")
		{
			float x,y,z;
			file >> x >> y>> z;

			if (file.fail())
			{
				errorEncountered = true;
				break;
			}

			vertices.push_back(Vector3f(x,y,z));
		}
		else if (token == "vt")
		{
			float s,t;
			file >> s >> t;

			if (file.fail())
			{
				errorEncountered = true;
				break;
			}

			vertTextureCoords.push_back(Vector2f(s,t));
		}
		else if (token == "vn")
		{
			float x,y,z;
			file >> x >> y>> z;

			if (file.fail())
			{
				errorEncountered = true;
				break;
			}

			vertNormals.push_back(Vector3f(x,y,z));
		}
		else if (token == "f")
		{
			std::stringstream line;

			char c;
			do
			{
				file.get(c);
				line << c;
			}
			while(file.peek() != '\n' && file.good());

			std::string indexstr;

			int count = 0;
			while (line.good())
			{
				line>>indexstr;

				if (!line.fail())
				{
				indices.push_back(ParseOBJIndex(indexstr));

				count++;

				// triangle fan -> triangles
				if (count > 3)
				{
					int end = indices.size()-1;
					// need to add 2 more vertices, first vertex and one before
					indices.push_back(indices[end-count+1]);
					indices.push_back(indices[end-1]);
				}
				}
			}
		}
		}

		file.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	tRead.Stop();

	hasVt = indices[0].hasVt;
	hasVn = indices[0].hasVn;

	int stride = 3;
	if (hasVt)
		stride += 2;

	if (hasVn)
		stride += 3;

	Timer tProcess;
	tProcess.Start();

	std::vector<OBJ_INDEX_CACHE> packedIndicesCache;
	packedIndicesCache.reserve(vertices.size());

	for (int i = 0; i < vertices.size(); i++)
	{
		packedIndicesCache.push_back(OBJ_INDEX_CACHE());
	}

	for (int i = 0; i < indices.size(); i++)
	{
		// not yet packed
		int v = indices[i].v-1;
		if (packedIndicesCache[v].packedPos == -1)
		{
			packedVertices.push_back(vertices[indices[i].v-1].X());
			packedVertices.push_back(vertices[indices[i].v-1].Y());
			packedVertices.push_back(vertices[indices[i].v-1].Z());
			packedIndicesCache[v].v = indices[i].v;

			if (hasVt)
			{
				packedVertices.push_back(vertTextureCoords[indices[i].vt-1].X());
				packedVertices.push_back(vertTextureCoords[indices[i].vt-1].Y());
				packedIndicesCache[v].vt = indices[i].vt;

			}

			if (hasVn)
			{
				packedVertices.push_back(vertNormals[indices[i].vn-1].X());
				packedVertices.push_back(vertNormals[indices[i].vn-1].Y());
				packedVertices.push_back(vertNormals[indices[i].vn-1].Z());
				packedIndicesCache[v].vn = indices[i].vn;
			}

			packedIndices.push_back((packedVertices.size()/stride)-1);

			packedIndicesCache[v].packedPos = (packedVertices.size()/stride)-1;
		}
		// otherwise search cache
		else
		{
			bool found = false;

			int index = indices[i].v;
			while (!found)
			{
				if (((!hasVn) || (hasVn && packedIndicesCache[index].vn == indices[i].vn)) && 
					((!hasVt) || (hasVt && packedIndicesCache[index].vt == indices[i].vt)))
				{

					packedIndices.push_back(packedIndicesCache[index].packedPos);
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

				packedVertices.push_back(vertices[indices[i].v-1].X());
				packedVertices.push_back(vertices[indices[i].v-1].Y());
				packedVertices.push_back(vertices[indices[i].v-1].Z());
				packedIndicesCache.back().v = indices[i].v;

				if (hasVt)
				{
					packedVertices.push_back(vertTextureCoords[indices[i].vt-1].X());
					packedVertices.push_back(vertTextureCoords[indices[i].vt-1].Y());
					packedIndicesCache.back().vt = indices[i].vt;

				}

				if (hasVn)
				{
					packedVertices.push_back(vertNormals[indices[i].vn-1].X());
					packedVertices.push_back(vertNormals[indices[i].vn-1].Y());
					packedVertices.push_back(vertNormals[indices[i].vn-1].Z());
					packedIndicesCache.back().vn = indices[i].vn;
				}

				packedIndices.push_back((packedVertices.size()/stride)-1);

				packedIndicesCache[index].next = packedIndicesCache.size()-1;
				packedIndicesCache.back().packedPos = (packedVertices.size()/stride)-1;
			}
		}
	}

	/*
	for (int i = 0; i < indices.size(); i++)
	{
		bool found = false;
		for (int v = 0; v < packedVertices.size()/stride; v++)
		{
			if (packedVertices[v*stride] == vertices[indices[i].v-1].X() &&
				packedVertices[v*stride+1] == vertices[indices[i].v-1].Y() &&
				packedVertices[v*stride+2] == vertices[indices[i].v-1].Z())
			{
				int vt = v*stride + 3;
				if ((hasVt && packedVertices[vt] == vertTextureCoords[indices[i].vt-1].X() &&
					packedVertices[vt+1] == vertTextureCoords[indices[i].vt-1].Y()) || !hasVt)
				{
					int vn = v*stride + 3;
					if (hasVt)
						vn+=2;

					if ((hasVn && packedVertices[vn] == vertNormals[indices[i].vn-1].X() &&
						 packedVertices[vn+1] == vertNormals[indices[i].vn-1].Y() &&
						 packedVertices[vn+2] == vertNormals[indices[i].vn-1].Z()) || ! hasVn)
					{
						found = true;
						packedIndices.push_back(v);
						break;
					}
				}
			}
		}

		if (!found)
		{
			packedVertices.push_back(vertices[indices[i].v-1].X());
			packedVertices.push_back(vertices[indices[i].v-1].Y());
			packedVertices.push_back(vertices[indices[i].v-1].Z());

			if (hasVt)
			{
				packedVertices.push_back(vertTextureCoords[indices[i].vt-1].X());
				packedVertices.push_back(vertTextureCoords[indices[i].vt-1].Y());
			}

			if (hasVn)
			{
				packedVertices.push_back(vertNormals[indices[i].vn-1].X());
				packedVertices.push_back(vertNormals[indices[i].vn-1].Y());
				packedVertices.push_back(vertNormals[indices[i].vn-1].Z());
			}

			packedIndices.push_back((packedVertices.size()/stride)-1);
		}
	}
	*/
	tProcess.Stop();
	t.Stop();
	std::cout << "OBJ (" << m_filename << ") loaded in " << t.GetTime() << "s [read: " 
		<< tRead.GetTime() << " process: " << tProcess.GetTime() << "]"<< std::endl;
}

void Model::LoadFromMD2File(std::ifstream&)
{
}

void Model::Draw()
{
	/*
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->Draw();
	*/

	int stride = 3*sizeof(float);

	if (hasVt)
		stride+=2*sizeof(float);

	if (hasVn)
		stride += 3*sizeof(float);

	glEnableClientState(GL_VERTEX_ARRAY);
	
	if (hasVt)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (hasVn)
		glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, stride,  &packedVertices[0]);
	
	if (hasVt)
	{
		glTexCoordPointer(2, GL_FLOAT, stride, &packedVertices[3]); 
	}

	if (hasVn)
	{
		int vnOffs = hasVt ? 5 : 3;
		glNormalPointer(GL_FLOAT, stride, &packedVertices[vnOffs]);
	}
	glDrawElements(GL_TRIANGLES, packedIndices.size(), GL_UNSIGNED_INT, &packedIndices[0]); 

	glDisableClientState(GL_VERTEX_ARRAY);

	if (hasVt)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (hasVn)
		glDisableClientState(GL_NORMAL_ARRAY);
}


Model::OBJ_FORMAT_INDEX Model::ParseOBJIndex(const std::string& face)
{
	std::stringstream facestrm;
	facestrm << face;

	int v;
	facestrm>>v;
	
	if (facestrm.eof())
		return OBJ_FORMAT_INDEX(v);

	OBJ_FORMAT_INDEX index(v);

	if (facestrm.get() != '/')
		return index;

	int vt;
	facestrm>>vt;

	if (facestrm.fail())
	{
		facestrm.clear();
	}
	else
	{
		index.SetVt(vt);
	}

	if (facestrm.get() != '/')
		return index;

	int vn;
	facestrm>>vn;

	if (!facestrm.fail())
		index.SetVn(vn);

	return index;
}