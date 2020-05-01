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
	//ͨ��Assimp�����ļ�
	Assimp::Importer impoter;
	const aiScene * scene =	impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	//��������Ƿ���ȷ
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << impoter.GetErrorString() << std::endl;
		return;
	}
	//���ģ���ļ�·��
	mDirectory = path.substr(0, path.find_last_of('/'));
	//�Ӹ��ڵ㿪ʼ�ݹ鴦��
	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	//����ÿ���ڵ��ÿһ������
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
	//data ��Ҫ����
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//����ÿһ������Ķ���
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;
		
		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;
		//�ж��Ƿ������ͼ����
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
	//1.�������
	std::vector<Texture> Maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//2.�����
	Maps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//3.������
	Maps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");//??�ǲ�������?
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//4. height??? ������ȷʵ������?
	Maps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_diffuse");
	textures.insert(textures.end(), Maps.begin(), Maps.end());
	//����һ��Mesh����(������д��������,����һ���ֲ�����,����̫��)
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		//�����ͼ�Ƿ��Ѿ������ع�
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
			tex.id = loadImage(filename.c_str());//assimp���Ѿ��Ż���Y�����õ�����
			tex.type = typeName;
			tex.path = str.C_Str();
			textures.push_back(tex);
			mTexturesLoaded.push_back(tex);
		}
	}
	return textures;
}
