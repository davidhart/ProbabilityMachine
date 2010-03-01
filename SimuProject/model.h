#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <string>
#include <fstream>

class Mesh;

#include "Vector3f.h"
#include "Vector2f.h"

class Model
{
private:
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

	class OBJ_INDEX_CACHE : public OBJ_FORMAT_INDEX
	{
	public:
		OBJ_INDEX_CACHE(int v);
		int next;
		int packedPos;
	};

	std::vector<Mesh*> m_meshes;
	std::string m_filename;

	std::vector<float> packedVertices;
	std::vector<int> packedIndices;

	float * m_vertexData;
	int * m_indexData;

public:
	Model(const std::string& filename);
	~Model();
	void Draw();
	void LoadFromOBJFile(std::ifstream& file);
	void LoadFromMD2File(std::ifstream& file);

private:
	static OBJ_FORMAT_INDEX ParseOBJIndex(const std::string& face);
};

#endif
