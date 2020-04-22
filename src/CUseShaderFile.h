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

	static void framebuffer_size_callback1(GLFWwindow*  wnd, int width, int height);
	void processInput1(GLFWwindow* wnd);
	static void mouse_callback1(GLFWwindow* wnd, double xpos, double ypos);
	

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

	//��ǰ֡����һ֡��ʱ���
	float m_deltaTime;
	//��һ֡�Ľ���ʱ��
	float m_lastTime;
	//ʹ��ÿ֡ʱ���������ͳһ���ٶ�,���ⲻͬ���ܵ��Ե���֡�ʲ�ͬ���ƶ��ٶȲ�ͬ
	//����ʹ���ڹ̶���ʱ�䳤����,�ƶ����ٶ�����ͬ��

	//��������ƶ�����ĸ����Ǻ�ƫ����
private:
	//�Ƿ��״�������
	bool m_first_mouse;

	double m_lastX;
	double m_lastY;
	float m_yaw;
	float m_pitch;



	//static CUseShaderFile* m_ins;
};