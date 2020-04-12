
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

	//������ɫ����
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"//����Я������ɫ��Ϣ
		"out vec3 ourColor;\n"//��ƬԪ��ɫ�������ɫ
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourColor = aColor;\n"
		"}\0";


	//ƬԪ��ɫ����
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n" //�ԽӶ�����ɫ��
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor, 1.0f);\n"
		"}\0";



	static void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height)
	{
		glViewport(0, 0, width, height);//�����Ӵ�����
	}

	void processInput(GLFWwindow* wnd)
	{
		//����Ƿ���esc��
		if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			//�رմ���QA
			glfwSetWindowShouldClose(wnd, true);
		}
	}

	//int main()
	int funcmain()
	{

// 		float vertices[] = {
// 		-0.5f, -0.5f, 0.0f,
// 		0.5f, -0.5f, 0.0f,
// 		-0.0f, 0.5f, 0.0f
// 		};
		//����Я����ɫ��Ϣ
		GLfloat vertices[] = {
			// λ��              // ��ɫ
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ���� ��ɫ
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���� ��ɫ
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ���� ��ɫ
		};
		//����������ɫ��ͬ,����ʾ��һ����ɫ���������㵽�м���ɵ�������.
		//��ɫ��������ΪƬԪ��ɫ��������Ƭ�β�ֵ(Fragment Interpolation)
		//�ڹ�դ���׶� ����ÿ��ƬԪ�������λ�ý��в�ֵ������ɫ�����������.�����������������������λ�þ������м�ƬԪ����ɫ


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
		GLFWwindow* wnd = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);
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


		//����,������ɫ������
		//������ɫ��
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		//ƬԪ��ɫ��
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		//������ɫ��
		int shaderProgram = glCreateProgram();//����һ����ɫ������
		glAttachShader(shaderProgram, vertexShader);//�Ѷ�����ɫ��������?
		glAttachShader(shaderProgram, fragmentShader);//��ƬԪ��ɫ��������?
		glLinkProgram(shaderProgram);//��֮Ϊ����?


		//�ͷ���ɫ��? ������ɾ�����?
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);//����Ψһid
		glBindVertexArray(VAO);//��

		glGenBuffers(1, &VBO);//����Ψһid
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//��
		//���� 1,����������Ҫ�������ĵط�(VBO) 2,�����С 3,�����ַ 4,�����Կ�����ʲô��ʽ�������� GL_STATIC_DRAWΪ����ı�����
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//������6Ϊÿ������Ĵ�С, ���Ϊÿ������λ����Ҫ��ƫ���� 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glUseProgram(shaderProgram);
		//ѭ����Ⱦ
		while (!glfwWindowShouldClose(wnd))
		{
			processInput(wnd);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f );
			glClear(GL_COLOR_BUFFER_BIT);//


			//������������ʱ��任��ɫ
// 			double timeValue = glfwGetTime();
// 			double greenValue = (sin(timeValue) / 2.0f) + 0.5f;
// 			double rValue = (cos(timeValue) / 2.0f) + 0.5f;
// 			double bValue = (tan(timeValue) / 2.0f) + 0.5f;
// 			int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//������滻��ƬԪ��ɫ���еı���,�Ӷ�ͨ���������
// 			
			//glUseProgram(shaderProgram);
			//����������������˳��Ҫ���,����Ϊ����uniform��ֵ,Ҫ������ȵ���glUseProgram
			//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//����ͻ�����ɫ��0��1֮��ѭ��
			//������Ҫ����4������,��ΪƬԪ��ɫ������Ҫ��vec4
			//glUniform4f(vertexColorLocation, rValue, greenValue, bValue, 1.0f);//��������rgb������ɫ���������
			//std::cout << rValue << " " << greenValue << " " << bValue << std::endl;

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
			//�������沢��ѯIO
			glfwSwapBuffers(wnd);
			glfwPollEvents();
		}


		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		glfwTerminate();
		return 0;
	}


};


