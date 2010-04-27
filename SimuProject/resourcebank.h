#ifndef _RESOURCEBANK_H
#define _RESOURCEBANK_H

#include <hash_map>
#include <string>

class Model;
class Texture;
class Material;
class Vector3f;
class TextureFile;

class ResourceBank
{
private:
	typedef stdext::hash_map<std::string, Model*> ModelHashMap;
	typedef stdext::hash_map<std::string, TextureFile*> TextureHashMap;
	typedef stdext::hash_map<std::string, Material*> MaterialHashMap;

	ModelHashMap m_modelMap;
	TextureHashMap m_textureMap;
	MaterialHashMap m_materialMap;

	bool m_loaded;

public:
	ResourceBank();
	virtual ~ResourceBank();
	
	Model* RequestModel(const std::string& model);
	Texture* RequestTexture(const std::string& texture);
	Material* RequestMaterial(const std::string& material);

	void Load();
	void Unload();

	void LoadMaterialsFromFile(const std::string& filename);

private:
	void AddMaterial(const std::string& material, 
		const std::string& kdMap, const Vector3f& Ka, const Vector3f& Kd, const Vector3f& Ks, float d, float Ns, int illum);
};

#endif