#pragma once

#include <glad/glad.h>//��Ҫ��glfwǰ ����ᱨ�������
#include <glfw/glfw3.h>
#include <iostream>


class CUseShaderFile {
public:
	CUseShaderFile();
	~CUseShaderFile();

	unsigned int loadImage(const char* path, bool bTransparency = false);
	int init();
	int texture();
	int triangle();

	void loop();
	void loop_texture();
private:

	static void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height);
	void processInput(GLFWwindow* wnd);



	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	GLFWwindow* m_wnd;
	unsigned int m_texture; //����ΨһID
	unsigned int m_texture2; //����ΨһID


};