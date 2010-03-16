#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <string>
#include <fstream>

#include "MaterialGroup.h"

class Mesh;

#include "Vector3f.h"
#include "Vector2f.h"

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
	MaterialGroup m_materialGroup;
	std::vector<Mesh*> m_meshes;
	std::string m_filename;

public:
	Model(const std::string& filename);
	~Model();
	void Draw();
	void Load();

private:
	void LoadFromOBJFile(std::ifstream& file);
	void LoadFromMD2File(std::ifstream& file);
	static OBJ_FORMAT_INDEX ParseOBJIndex(const std::string& face);
};

#endif
