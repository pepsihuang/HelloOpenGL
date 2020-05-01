#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include "CShaderFromFile.h"
#include <vector>

/*
基础数据 网格
Mash类在构造中就会对数据进行加载处理.变成直接可绘制的状态
Draw则是每一帧中调用,直接进行绘制.
*/

//一个顶点数据
struct Vertex {
	//坐标
	glm::vec3 Position;
	//法向量
	glm::vec3 Normal;
	//贴图UV坐标
	glm::vec2 TexCoords;
	//todo ??
	glm::vec3 Tangent;
	//todo ??
	glm::vec3 Bitangent;
};

//贴图数据
struct Texture {
	unsigned int id;
	//类型
	std::string type;
	//存储纹理的路径用于与其他纹理比较,避免重复加载相同贴图
	std::string path;
};

//网格
class Mesh {
public:
	//数据
	//一组顶点
	std::vector<Vertex> mVertexs;
	//一组索引
	std::vector<unsigned int> mIndices;
	//一组贴图
	std::vector<Texture> mTextures;
	unsigned int mVAO;

	Mesh(std::vector<Vertex>& vertexs, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	//render this mesh
	void Draw(CShaderFromFile& shader);
private:
	unsigned int mVBO, mEBO;
	void setupMesh();
};