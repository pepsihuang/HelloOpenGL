#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include "CShaderFromFile.h"
#include <vector>

/*
�������� ����
Mash���ڹ����оͻ�����ݽ��м��ش���.���ֱ�ӿɻ��Ƶ�״̬
Draw����ÿһ֡�е���,ֱ�ӽ��л���.
*/

//һ����������
struct Vertex {
	//����
	glm::vec3 Position;
	//������
	glm::vec3 Normal;
	//��ͼUV����
	glm::vec2 TexCoords;
	//todo ??
	glm::vec3 Tangent;
	//todo ??
	glm::vec3 Bitangent;
};

//��ͼ����
struct Texture {
	unsigned int id;
	//����
	std::string type;
	//�洢�����·����������������Ƚ�,�����ظ�������ͬ��ͼ
	std::string path;
};

//����
class Mesh {
public:
	//����
	//һ�鶥��
	std::vector<Vertex> mVertexs;
	//һ������
	std::vector<unsigned int> mIndices;
	//һ����ͼ
	std::vector<Texture> mTextures;
	unsigned int mVAO;

	Mesh(std::vector<Vertex>& vertexs, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	//render this mesh
	void Draw(CShaderFromFile& shader);
private:
	unsigned int mVBO, mEBO;
	void setupMesh();
};