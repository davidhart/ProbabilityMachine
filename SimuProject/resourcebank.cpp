#include "resourcebank.h"

#include "texturefile.h"
#include "model.h"
#include "material.h"

#include <fstream>
#include <limits>

using std::string;
using std::ifstream;

ResourceBank::ResourceBank() : 
	m_loaded ( false )
{

}

ResourceBank::~ResourceBank()
{
	for (ModelHashMap::iterator i = m_modelMap.begin(); i != m_modelMap.end(); ++i)
	{
		delete i->second;
	}

	for (TextureHashMap::iterator i = m_textureMap.begin(); i != m_textureMap.end(); ++i)
	{
		delete i->second;
	}

	for (MaterialHashMap::iterator i = m_materialMap.begin(); i != m_materialMap.end(); ++i)
	{
		delete i->second;
	}
}
	
Model* ResourceBank::RequestModel(const std::string& model)
{
	ModelHashMap::iterator i = m_modelMap.find(model);

	if (i != m_modelMap.end())
		return i->second;
	else
	{
		Model * m = new Model(model, this);
		
		if(m_loaded)
			m->Load();

		m_modelMap[model] = m;
		return m;
	}
}

Texture* ResourceBank::RequestTexture(const std::string& texture)
{
	TextureHashMap::iterator i = m_textureMap.find(texture);

	if (i != m_textureMap.end())
		return i->second;
	else
	{
		TextureFile *t = new TextureFile(texture);

		if (m_loaded)
			t->Load();

		m_textureMap[texture] = t;
		return t;
	}
}

Material* ResourceBank::RequestMaterial(const std::string& material)
{
	MaterialHashMap::iterator i = m_materialMap.find(material);

	if (i != m_materialMap.end())
		return i->second;
	else
	{
		Material* m = new Material();
		m_materialMap[material] = m;
		return m;
	}
}

void ResourceBank::Load()
{
	if (!m_loaded)
	{
		for (TextureHashMap::iterator i = m_textureMap.begin(); i != m_textureMap.end(); ++i)
		{
			i->second->Load();
		}
		for (ModelHashMap::iterator i = m_modelMap.begin(); i != m_modelMap.end(); ++i)
		{
			i->second->Load();
		}
		m_loaded = true;
	}
}

void ResourceBank::Unload()
{
	if (m_loaded)
	{
		for (TextureHashMap::iterator i = m_textureMap.begin(); i != m_textureMap.end(); ++i)
		{
			i->second->Unload();
		}
		for (ModelHashMap::iterator i = m_modelMap.begin(); i != m_modelMap.end(); ++i)
		{
			i->second->Unload();
		}
		m_loaded = false;
	}
}

void ResourceBank::LoadMaterialsFromFile(const std::string &filename)
{
	// .mtl format
	ifstream mtlFile(filename.c_str());

	if (mtlFile.good())
	{
		string currentMaterial, currentMapKd;
		int currentIllum = 0;
		float currentD = 0, currentNs = 0;

		Vector3f currentKa, currentKd, currentKs;

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

void ResourceBank::AddMaterial(const std::string& material, 
	const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum)
{
	Texture * t;
	if (kdMap.empty())
		t = NULL;
	else
		t = RequestTexture(kdMap);

	MaterialHashMap::iterator i = m_materialMap.find(material);
	
	if (i != m_materialMap.end())
	{
		Material * m = i->second;

		m->SetTexture(t);
		m->SetAmbient(Ka);
		m->SetDiffuse(Kd);
		m->SetSpecular(Ks);
		m->SetAlpha(d);
		m->SetShininess(Ns);
		m->SetLightingMode(illum);
	}
	else
	{
		m_materialMap[material] = new Material(t, Ka, Kd, Ks, d, Ns, illum);
	}
}