#ifndef _OPENGL_HELLO_WORLD_MAIN_H_
#define _OPENGL_HELLO_WORLD_MAIN_H_


#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height)
{
	glViewport(0, 0, width, height);//�����Ӵ�����
}

void processInput(GLFWwindow* wnd)
{
	//����Ƿ���esc��
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//�رմ���
		glfwSetWindowShouldClose(wnd, true);
	}
}

int main()
{
	std::cout << "Hello OpenGL!" << std::endl;
	//��ʼ��
	glfwInit();
	//OpenGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//OpenGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//OpenGL����ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow* wnd = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
	if (!wnd)
	{
		std::cout << "����ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}
	//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(wnd);

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout<< "��ʼ��gladʧ��" << std::endl;
		return -1;
	}
	//ע�ᴰ�ڻص�
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


