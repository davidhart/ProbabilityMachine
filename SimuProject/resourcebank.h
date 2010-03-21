#ifndef _RESOURCEBANK_H
#define _RESOURCEBANK_H

#include <hash_map>
#include <string>

class Model;
class Texture;
class Material;
class Vector3f;

class ResourceBank
{
private:
	typedef stdext::hash_map<std::string, Model*> ModelHashMap;
	typedef stdext::hash_map<std::string, Texture*> TextureHashMap;
	typedef stdext::hash_map<std::string, Material*> MaterialHashMap;

	ModelHashMap m_modelMap;
	TextureHashMap m_textureMap;
	MaterialHashMap m_materialMap;

public:
	virtual ~ResourceBank();
	
	Model* RequestModel(const std::string& model);
	Texture* RequestTexture(const std::string& texture);
	Material* RequestMaterial(const std::string& material);

	void LoadMaterialsFromFile(const std::string& filename);
	void AddMaterial(const std::string& material, 
		const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum);
};

#endif