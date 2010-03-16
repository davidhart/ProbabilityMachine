#include "materialgroup.h"
#include "material.h"

#include <limits>
#include <fstream>

#include "Vector3f.h"

using std::string;
using std::ifstream;

MaterialGroup::MaterialGroup()
{
}

MaterialGroup::~MaterialGroup()
{
	MaterialHashMap::iterator i = m_materials.begin();
	while (i != m_materials.end())
	{
		delete i->second;
		i++;
	}
}

void MaterialGroup::LoadMaterialsFromFile(const std::string &filename)
{
	// assume .mtl format
	ifstream mtlFile(filename.c_str());

	if (mtlFile.good())
	{
		string currentMaterial;
		string currentMapKd;
		int currentIllum = 0;
		float currentD = 0;
		float currentNs = 0;

		Vector3f currentKa;
		Vector3f currentKd;
		Vector3f currentKs;

		string token;

		while (!mtlFile.eof())
		{
			if (!mtlFile.fail())
			{
				mtlFile >> token;

				if (token == "newmtl")
				{
					if (!currentMaterial.empty())
					{
						AddMaterial(currentMaterial, currentMapKd, 
									currentKa, currentKd, currentKs, 
									currentD, currentNs, 
									currentIllum);
					}

					mtlFile >> currentMaterial;

					currentIllum = 1;
					currentNs = 0.0f;
					currentD = 1.0f;

					currentKa.SetX(0.2f);
					currentKa.SetY(0.2f);
					currentKa.SetZ(0.2f);

					currentKd.SetX(0.8f);
					currentKd.SetY(0.8f);
					currentKd.SetZ(0.8f);

					currentKs.SetX(1.0f);
					currentKs.SetY(1.0f);
					currentKs.SetZ(1.0f);

					currentMapKd.clear();
				}
				else if (token == "Ns")
				{
					mtlFile >> currentNs;
				}
				
				else if (token == "Ka")
				{
					mtlFile >> currentKa;
				}
				else if (token == "Kd")
				{
					mtlFile >> currentKd;
				}
				else if (token == "Ks")
				{
					mtlFile >> currentKs;
				}
				/* not going to support this feature - density/refractive index
				else if (token == "Ni")
				{
					mtlFile >> currentNi;
				}
				*/
				else if (token == "d" || token == "Tr")
				{
					mtlFile >> currentD;
				}
				else if (token == "illum")
				{
					mtlFile >> currentIllum;
				}
				else if (token == "map_Kd")
				{
					mtlFile >> currentMapKd;
				}
			}
			else
			{
				mtlFile.clear();
			}

			
			mtlFile.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}

		mtlFile.close();

		if (!currentMaterial.empty())
			AddMaterial(currentMaterial, currentMapKd, 
						currentKa, currentKd, currentKs, 
						currentD, currentNs,
						currentIllum);

	}	
}

Material& MaterialGroup::RequestMaterial(const std::string& materialName)
{
	MaterialHashMap::iterator m = m_materials.find(materialName);

	if (m == m_materials.end())
	{
		Material* m = new Material();
		m_materials[materialName] = m;
		return *m;
	}
	else
	{
		return *m->second;
	}
}

void MaterialGroup::Load()
{
	MaterialHashMap::iterator i = m_materials.begin();
	while (i != m_materials.end())
	{
		i->second->Load();
		i++;
	}
}

void MaterialGroup::AddMaterial(const std::string& materialName, 
		const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum)
{
	if (m_materials.find(materialName) != m_materials.end())
		return;

	m_materials[materialName] = new Material(kdMap, Ka, Kd, Ks, d, Ns, illum);
}