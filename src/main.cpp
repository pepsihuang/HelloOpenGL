#ifndef _OPENGL_HELLO_WORLD_MAIN_H_
#define _OPENGL_HELLO_WORLD_MAIN_H_


#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height)
{
	glViewport(0, 0, width, height);//调整视窗区域
}

void processInput(GLFWwindow* wnd)
{
	//检查是否按下esc键
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//关闭窗口
		glfwSetWindowShouldClose(wnd, true);
	}
}

int main()
{
	std::cout << "Hello OpenGL!" << std::endl;
	//初始化
	glfwInit();
	//OpenGL主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//OpenGL副版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//OpenGL我们使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* wnd = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
	if (!wnd)
	{
		std::cout << "创建失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(wnd);

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<< "初始化glad失败" << std::endl;
		return -1;
	}
	//注册窗口回调
	glfwSetFramebufferSizeCallback(wnd, framebuffer_size_callback);

	while (!glfwWindowShouldClose(wnd))
	{
		processInput(wnd);

		glClearColor(.0f, 0.0f, 1.0f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT);//

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



#endif


