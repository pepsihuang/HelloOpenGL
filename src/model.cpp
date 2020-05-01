#include "model.h"
#include <iostream>
#include "../include/assimp/mesh.h"
#include "Global.h"

Model::Model(const std::string & path, bool gamma)
{
	loadModel(path);
	std::cout << "Model load finish: " << path << std::endl;
}

void Model::Draw(CShaderFromFile& shader)
{
	for (unsigned int i = 0; i < mMeshs.size(); ++i)
	{
		mMeshs[i].Draw(shader);
	}
}

void Model::loadModel(const std::string& path)
{
	//通过Assimp加载文件
	Assimp::Importer impoter;
	const aiScene * scene =	impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	//检查输入是否正确
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << impoter.GetErrorString() << std::endl;
		return;
	}
	//获得模型文件路径
	mDirectory = path.substr(0, path.find_last_of('/'));
	//从根节点开始递归处理
	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	//处理每个节点的每一个网格
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		//
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshs.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	//data 需要填充的
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//处理每一个网格的顶点
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;
		
		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;
		//判断是否包含贴图坐标
		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertex.Tangent.x = mesh->mTangents[i].x;
		vertex.Tangent.y = mesh->mTangents[i].y;
		vertex.Tangent.z = mesh->mTangents[i].z;

		vertex.Bitangent.x = mesh->mBitangents[i].x;
		vertex.Bitangent.y = mesh->mBitangents[i].y;
		vertex.Bitangent.z = mesh->mBitangents[i].z;

		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	//diffuse
	//1.漫反射光
	std::vector<Texture> Maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//2.镜面光
	Maps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//3.法向量
	Maps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");//??是不是有误?
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//4. height??? 但参数确实环境光?
	Maps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_diffuse");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//返回一个Mesh对象(这样的写法并不好,返回一个局部变量,开销太大)
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		//检查贴图是否已经被加载过
		bool skip = false;
		for (unsigned int j = 0; j < mTexturesLoaded.size(); ++j)
		{
			std::string  cmpc = str.C_Str();
			if (mTexturesLoaded[j].path == cmpc)
			{
				textures.push_back(mTexturesLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture tex;
			std::string filename = std::string(str.C_Str());
			filename = mDirectory + '/' + filename;
			tex.id = loadImage(filename.c_str());//assimp库已经优化了Y方向倒置的问题
			tex.type = typeName;
			tex.path = str.C_Str();
			textures.push_back(tex);
			mTexturesLoaded.push_back(tex);
		}
	}
	return textures;
}
