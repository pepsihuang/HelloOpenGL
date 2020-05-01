#pragma once

/*
模型加载类
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
	//模型数据
	std::vector<Texture> mTexturesLoaded;//保存全部加载的贴图,确保一个贴图只会被加载一次
	std::vector<Mesh> mMeshs;
	std::string mDirectory;
	bool mGammaCorrection;//?貌似没见到有讲伽马校正相关的东西

	Model(const std::string& path, bool gamma = false);
	void Draw(CShaderFromFile& shader);

private:
	//使用Assimp库从文件中加载模型,并存储结果网格到mMeshs数组中
	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};