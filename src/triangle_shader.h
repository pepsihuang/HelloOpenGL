
#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

class TriangleShader {



public:
	TriangleShader() {}
	~TriangleShader(){}

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
		"uniform vec4 outColor;" //给代码预留一个变量
		"void main()\n"
		"{\n"
		"	FragColor = outColor;\n"
		"}\0";



	static void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height)
	{
		glViewport(0, 0, width, height);//调整视窗区域
	}

	void processInput(GLFWwindow* wnd)
	{
		//检查是否按下esc键
		if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			//关闭窗口QA
			glfwSetWindowShouldClose(wnd, true);
		}
	}

	//int main()
	int funcmain()
	{

		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.0f, 0.5f, 0.0f
		};



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
		glGenVertexArrays(1, &VAO);//生成唯一id
		glBindVertexArray(VAO);//绑定

		glGenBuffers(1, &VBO);//生成唯一id
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定
		//参数 1,顶点数据需要拷贝到的地方(VBO) 2,数组大小 3,数组地址 4,告诉显卡采用什么方式管理数据 GL_STATIC_DRAW为无须改变数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		//循环渲染
		while (!glfwWindowShouldClose(wnd))
		{
			processInput(wnd);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f );
			glClear(GL_COLOR_BUFFER_BIT);//


			//让三角形随着时间变换颜色
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			float rValue = (cos(timeValue) / 2.0f) + 0.5f;
			float bValue = (tan(timeValue) / 2.0f) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//这里就替换了片元着色器中的变量,从而通过代码控制
			
			glUseProgram(shaderProgram);
			//上下两个方法是有顺序要求的,下面为更新uniform的值,要求必须先调用glUseProgram
			//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//这里就会让绿色从0到1之间循环
			//这里需要传递4个参数,因为片元着色器中需要的vec4
			glUniform4f(vertexColorLocation, rValue, greenValue, bValue, 1.0f);//这里是让rgb三种颜色都随机起来
			std::cout << rValue << " " << greenValue << " " << bValue << std::endl;

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
			//交换缓存并查询IO
			glfwSwapBuffers(wnd);
			glfwPollEvents();
		}

		glfwTerminate();
		return 0;
	}


};


