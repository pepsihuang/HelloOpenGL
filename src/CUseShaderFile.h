#pragma once

#include <glad/glad.h>//��Ҫ��glfwǰ ����ᱨ�������
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
	//�����ת������
	void loop_texture_3ds();
	//ʹ�ü��̲����ƶ����
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
	unsigned int m_texture; //����ΨһID
	unsigned int m_texture2; //����ΨһID

	CShaderFromFile* m_shader;

	float m_cur_mix;


	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};