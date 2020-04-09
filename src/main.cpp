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

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//顶点着色代码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//片元着色代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f,);\n"
"}\0";

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.0f, 0.5f, 0.0f
};

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
	GLFWwindow* wnd = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);
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


	//创建,编译着色器程序
	//顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//片元着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//释放着色器?
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//循环渲染
	while (!glfwWindowShouldClose(wnd))
	{
		processInput(wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT);//

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



#endif


