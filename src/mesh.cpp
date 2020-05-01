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
		
		//设置采样器到正确的贴图单元
		//name += number;
		shader.setFloat((name + number).c_str(), i);
		//最终绑定到贴图
		glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
	}

	//绘制网格
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//永远保持良好的习惯:再次设置所有东西回归到默认?
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{

	//创建缓存
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);
	//加载数据到顶点缓存
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, mVertexs.size() * sizeof(Vertex), &mVertexs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	//设置顶点属性指定位移
	//顶点坐标
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//顶点法向量
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));//offsetof是个好同志,直接获得结构体中对应的偏移位置

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}
