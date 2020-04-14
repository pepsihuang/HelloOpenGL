#include "CUseShaderFile.h"
#include "CShaderFromFile.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"





void CUseShaderFile::framebuffer_size_callback(GLFWwindow* wnd, int width, int height)
{
	glViewport(0, 0, width, height);//调整视窗区域
}

void CUseShaderFile::processInput(GLFWwindow* wnd)
{
	//检查是否按下esc键
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//关闭窗口QA
		glfwSetWindowShouldClose(wnd, true);
	}
}

CUseShaderFile::CUseShaderFile() :m_wnd(NULL)
{
	init();
}

CUseShaderFile::~CUseShaderFile()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate();
}

void CUseShaderFile::loadImage(const char* path)
{
	if (!path)
	{
		std::cout << "CUseShaderFile::loadImage: image path ERR!" << std::endl;
		return;
	}
	int width, height, nrChannels;//最后为颜色通道的个数
	unsigned char* data = stbi_load("../path/wall.jpg", &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "CUseShaderFile::loadImage: FAILED to load texture:" << path << std::endl;
		return;
	}
	
	//参数一 为生成纹理的数量
	glGenTextures(1, &m_texture);
	//把前面载入的图片数据生成一个纹理
	glTexImage2D(
		GL_TEXTURE_2D, //纹理目标
		0, //多级渐远纹理的级别，0为基础级别
		GL_RGB, //期望的纹理存储格式
		width, //纹理高宽
		height, 
		0, //只能为0 OpenGL辣鸡代码
		GL_RGB, //原图的格式和数据类型
		GL_UNSIGNED_BYTE, 
		data);//参数数据
	glGenerateMipmap(GL_TEXTURE_2D);

	//释放纹理
	stbi_image_free(data);

}

int CUseShaderFile::init()
{
	std::cout << "Hello OpenGL!" << std::endl;
	//初始化
	glfwInit();
	//OpenGL主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//OpenGL副版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//OpenGL我们使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	m_wnd = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);
	if (!m_wnd)
	{
		std::cout << "创建失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(m_wnd);
	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "初始化glad失败" << std::endl;
		return -1;
	}
	//注册窗口回调
	glfwSetFramebufferSizeCallback(m_wnd, framebuffer_size_callback);

	//生成唯一id
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	return 0;
}
int CUseShaderFile::texture()
{
	//纹理应用点
	float tex_vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上		
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertices), tex_vertices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	loadImage("../path/wall.jpg");





	return 0;

}
int CUseShaderFile::triangle()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.0f, 0.5f, 0.0f
	};


	//参数 1,顶点数据需要拷贝到的地方(VBO) 2,数组大小 3,数组地址 4,告诉显卡采用什么方式管理数据 GL_STATIC_DRAW为无须改变数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//参数 1, 对应的顶点属性编号(location=0) 2,顶点属性的大小 
	//3,数据类型 4,指明是否需要规范化(暂时不知道是什么东西) 
	//5,属性跨度 即数组中每三个为一组
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	return 0;
}

void CUseShaderFile::loop()
{

	CShaderFromFile shader("../path/Shader.vs", "../path/Shader.fs");

	//循环渲染
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		shader.use();
		double timeValue = glfwGetTime();
		double Value = (sin(timeValue) / 2.0f);
		shader.setFloat("xoffset", (float)Value);

		//glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

}

void CUseShaderFile::loop_texture()
{
	CShaderFromFile shader("../path/tex_shader.vs", "../path/tex_shader.fs");

	//循环渲染
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		glBindTexture(GL_TEXTURE_2D, m_texture);

		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

	glfwTerminate();

}
