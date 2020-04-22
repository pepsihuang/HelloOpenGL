#pragma once
#include <glad/glad.h>//��Ҫ��glfwǰ ����ᱨ�������
#include <glfw/glfw3.h>
#include <iostream>

/*
�����õķ������ϳ�Ϊ���� 

1. ��ʼ��������Ϣ
2. ѭ������
*/
class CBase
{
public:
	CBase();
	virtual ~CBase();

	void Loop();

	virtual void OnProcessInput(GLFWwindow* wnd) {}
	virtual void OnMouseCallBack(GLFWwindow* wnd, double xpos, double ypos) {}
	virtual void OnScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {}

	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
private:

	int init();
	virtual void OnLoop() {}
	virtual void BeforeLoop(){}

	void processInput(GLFWwindow* wnd);

private:

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	GLFWwindow* m_wnd;
};

