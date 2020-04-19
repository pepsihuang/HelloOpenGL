#pragma once

#include <glad/glad.h>//需要在glfw前 否则会报编译错误
#include <glfw/glfw3.h>
#include <iostream>
#include "CShaderFromFile.h"


class CUseShaderFile {
public:
	CUseShaderFile();
	~CUseShaderFile();

	unsigned int loadImage(const char* path, bool bTransparency = false);
	int init();
	int texture();
	int triangle();
	
	int texture_3d();

	void loop();
	void loop_texture();
	void loop_texture_3d();
	//多个旋转立方体
	void loop_texture_3ds();
	//使用键盘操作移动相机
	void loop_key_move_cam();

	void UseMat4(const CShaderFromFile* shader);
	void UseMat4_move(const CShaderFromFile* shader);
private:

	static void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height);
	void processInput(GLFWwindow* wnd);

	void exit();
	void print(const std::string& str, const glm::vec3& vec);


	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	GLFWwindow* m_wnd;
	unsigned int m_texture; //纹理唯一ID
	unsigned int m_texture2; //纹理唯一ID

	CShaderFromFile* m_shader;

	float m_cur_mix;


	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};