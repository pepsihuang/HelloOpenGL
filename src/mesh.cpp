#include "mesh.h"
#include <string>



Mesh::Mesh(std::vector<Vertex>& vertexs, std::vector<unsigned int>& indices, std::vector<Texture>& textures) 
{
	mVertexs.insert(mVertexs.end(), vertexs.begin(), vertexs.end());
	mIndices.insert(mIndices.end(), indices.begin(), indices.end());
	mTextures.insert(mTextures.end(), textures.begin(), textures.end());
	setupMesh();
}
//render
void Mesh::Draw(CShaderFromFile& shader)
{
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;//??
	for (unsigned int i = 0; i < mTextures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = mTextures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);
		
		//���ò���������ȷ����ͼ��Ԫ
		//name += number;
		shader.setFloat((name + number).c_str(), i);
		//���հ󶨵���ͼ
		glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
	}

	//��������
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//��Զ�������õ�ϰ��:�ٴ��������ж����ع鵽Ĭ��?
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{

	//��������
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);
	//�������ݵ����㻺��
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, mVertexs.size() * sizeof(Vertex), &mVertexs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	//���ö�������ָ��λ��
	//��������
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//���㷨����
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));//offsetof�Ǹ���ͬ־,ֱ�ӻ�ýṹ���ж�Ӧ��ƫ��λ��

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}
