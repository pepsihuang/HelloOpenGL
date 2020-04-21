#pragma once


namespace HDAN_COLOR {

	#include <glad/glad.h>//需要在glfw前 否则会报编译错误
	#include <glfw/glfw3.h>
	#include <iostream>

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>

	#include "CShaderFromFile.h"
	#include "Camera.h"

	void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height);
	void processInput(GLFWwindow* wnd);
	void mouse_callback(GLFWwindow* wnd, double xpos, double ypos);
	void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset);

	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2;
	float lastY = SCR_HEIGHT / 2;
	bool firstMouse = true;

	
	void funcmain()
	{
		CShaderFromFile shader("path/shader.vs", "path/shader.vs");
		Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
		std::cout<<"funcmain"<<std::endl;
	
	}



	void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height)
	{

	}

	void processInput(GLFWwindow* wnd)
	{

	}

	void mouse_callback(GLFWwindow* wnd, double xpos, double ypos)
	{

	}
	void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset)
	{

	}

};
