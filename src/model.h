#pragma once

/*
ģ�ͼ�����
*/
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "mesh.h"
#include <string>

class Model
{
public:
	//ģ������
	std::vector<Texture> mTexturesLoaded;//����ȫ�����ص���ͼ,ȷ��һ����ͼֻ�ᱻ����һ��
	std::vector<Mesh> mMeshs;
	std::string mDirectory;
	bool mGammaCorrection;//?ò��û�����н�٤��У����صĶ���

	Model(const std::string& path, bool gamma = false);
	void Draw(CShaderFromFile& shader);

private:
	//ʹ��Assimp����ļ��м���ģ��,���洢�������mMeshs������
	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};