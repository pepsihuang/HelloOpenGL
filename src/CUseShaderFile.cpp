#include "CUseShaderFile.h"
#include "CShaderFromFile.h"





void CUseShaderFile::framebuffer_size_callback(GLFWwindow* wnd, int width, int height)
{
	glViewport(0, 0, width, height);//�����Ӵ�����
}

void CUseShaderFile::processInput(GLFWwindow* wnd)
{
	//����Ƿ���esc��
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//�رմ���QA
		glfwSetWindowShouldClose(wnd, true);
	}
}

int CUseShaderFile::funcmain()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.0f, 0.5f, 0.0f
	};
	std::cout << "Hello OpenGL!" << std::endl;
	//��ʼ��
	glfwInit();
	//OpenGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//OpenGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//OpenGL����ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
		std::cout << "��ʼ��gladʧ��" << std::endl;
		return -1;
	}
	//ע�ᴰ�ڻص�
	glfwSetFramebufferSizeCallback(wnd, framebuffer_size_callback);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);//����Ψһid
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���� 1,����������Ҫ�������ĵط�(VBO) 2,�����С 3,�����ַ 4,�����Կ�����ʲô��ʽ�������� GL_STATIC_DRAWΪ����ı�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//���� 1, ��Ӧ�Ķ������Ա��(location=0) 2,�������ԵĴ�С 
	//3,�������� 4,ָ���Ƿ���Ҫ�淶��(��ʱ��֪����ʲô����) 
	//5,���Կ�� ��������ÿ����Ϊһ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	CShaderFromFile shader("../path/Shader.vs", "../path/Shader.fs");

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(wnd))
	{
		processInput(wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		shader.use();
		double timeValue = glfwGetTime();
 		double Value = (sin(timeValue) / 2.0f) + 0.5f;
		shader.setFloat("xoffset", Value);
		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
