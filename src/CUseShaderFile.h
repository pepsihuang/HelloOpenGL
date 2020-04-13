#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>


class CUseShaderFile {
public:
	CUseShaderFile(){}
	~CUseShaderFile() {}

	int funcmain();

private:

	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	static void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height);
	void processInput(GLFWwindow* wnd);


};