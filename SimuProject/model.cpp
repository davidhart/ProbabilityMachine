#include "model.h"
#include "mesh.h"
#include "timer.h"
#include "resourcebank.h"

#include <windows.h>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

#include <GL/gl.h>

using std::string;

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

Model::Model(const std::string& filename, ResourceBank* resources) :
	m_filename ( filename ), 
	m_loaded ( false )
{
	std::ifstream file(filename.c_str());

	// if the file could be opened
	if(file.good())
	{
		LoadFromOBJFile(file, resources);

		file.close();
	}
	else
	{
		std::cout << "MODEL (" << filename << ") File could not be read" << std::endl;
	}
}

Model::~Model()
{
	Unload();

	for (unsigned int i = 0; i < m_meshes.size(); i++)
		delete m_meshes[i];
}

void Model::LoadFromOBJFile(std::ifstream& file, ResourceBank* resources)
{
	Timer t;
	t.Start();
	std::vector<Vector3f> vertices;
	std::vector<Vector3f> vertNormals;
	std::vector<Vector2f> vertTextureCoords;
	std::vector<OBJ_FORMAT_INDEX> indices;
	
	std::string token;

	std::string material;

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
		else if (token == "#")
		{

		}
		else if (token == "usemtl")
		{
			file >> material;

			if (indices.size() > 0)
			{
				m_meshes.push_back(new Mesh(vertices, vertNormals, vertTextureCoords, indices, resources->RequestMaterial(material)));
			}

			indices.clear();
		}
		else if (token == "mtllib")
		{
				string materialLibFileName;

				file >> materialLibFileName;

				if (!file.fail())
				{
					int i;
					for (i = m_filename.size()-1; i >= 0; i--)
					{
						if( m_filename[i] == '\\' || m_filename[i] == '/' )
							break;
					}

					string relativeDirLibName = m_filename.substr(0,i+1) + materialLibFileName;

					resources->LoadMaterialsFromFile(relativeDirLibName);
				}
		}
		}
		else
		{
			file.clear();
		}

		file.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	}

	if (indices.size() > 0)
	{
		m_meshes.push_back(new Mesh(vertices, vertNormals, vertTextureCoords, indices, resources->RequestMaterial(material)));
	}

	t.Stop();
	std::cout << "MODEL (" << m_filename << ") fetched  in " << t.GetTime() << "s [" << m_meshes.size() <<" surfaces]" << std::endl;
}

void Model::Draw()
{
	if (m_loaded)
		for (unsigned int i = 0; i < m_meshes.size(); i++)
			m_meshes[i]->Draw();
}

void Model::Load()
{
	if (!m_loaded)
	{
		Timer t;
		t.Start();

		for (unsigned int i = 0; i < m_meshes.size(); i++)
			m_meshes[i]->Load();

		m_loaded = true;

		t.Stop();
		
		std::cout << "MODEL (" << m_filename << ") loaded in " << t.GetTime() << "s" << std::endl;
	}
}

void Model::Unload()
{
	if (m_loaded)
	{
		for (unsigned int i = 0; i < m_meshes.size(); i++)
			m_meshes[i]->Unload();

		m_loaded = false;
	}
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