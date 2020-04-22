#pragma once
#include <glad/glad.h>//需要在glfw前 否则会报编译错误
#include <glfw/glfw3.h>
#include <iostream>

/*
将公用的方法集合成为基类 

1. 初始化窗口信息
2. 循环主体
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

