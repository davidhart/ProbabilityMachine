#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <string>
#include <fstream>

class Mesh;

#include "Vector3f.h"
#include "Vector2f.h"

class ResourceBank;

class Model
{
public:
	class OBJ_FORMAT_INDEX
	{
	public:
		OBJ_FORMAT_INDEX(int v);
		OBJ_FORMAT_INDEX(int v, int vt, int vn);

		void SetVt(int vt);
		void SetVn(int vn);

		int v;
		int vt;
		int vn;

		bool hasVn;
		bool hasVt;
	};

	typedef std::vector<Vector3f> Vertex3fVector;
	typedef std::vector<Vector2f> Vertex2fVector;
	typedef std::vector<OBJ_FORMAT_INDEX> ObjIndicesVector;

private:
	std::vector<Mesh*> m_meshes;
	std::string m_filename;

	bool m_loaded;

public:
	Model(const std::string& filename, ResourceBank* resources);
	~Model();
	void Draw();
	void Load();
	void Unload();

private:
	void LoadFromOBJFile(std::ifstream& file, ResourceBank* resources);
	static OBJ_FORMAT_INDEX ParseOBJIndex(const std::string& face);
};

#endif
