#ifndef _MATERIALGROUP_H
#define _MATERIALGROUP_H

#include <string>
#include <hash_map>

class Material;
class Vector3f;

class MaterialGroup
{
private:
	typedef stdext::hash_map<std::string, Material*> MaterialHashMap;
	MaterialHashMap m_materials;

public:
	MaterialGroup();
	~MaterialGroup();

	void LoadMaterialsFromFile(const std::string& filename);

	Material& RequestMaterial(const std::string& materialName);
	void Load();

private:
	void AddMaterial(const std::string& materialName, 
		const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum);
};

#endif