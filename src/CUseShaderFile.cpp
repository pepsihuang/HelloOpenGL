#include "CUseShaderFile.h"
#include "CShaderFromFile.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"





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

unsigned int CUseShaderFile::loadImage(const char* path, bool bTransparency)
{
	if (!path)
	{
		std::cout << "CUseShaderFile::loadImage: image path ERR!" << std::endl;
		return 0;
	}
	int width, height, nrChannels;//���Ϊ��ɫͨ���ĸ���
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "CUseShaderFile::loadImage: FAILED to load texture:" << path << std::endl;
		return 0;
	}
	unsigned int texture;
	//����һ Ϊ�������������
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//Ϊ��ǰ�󶨵�����������û���,���˷�ʽ
	/*
	���Ʒ�ʽ	����
	GL_REPEAT	�������Ĭ����Ϊ���ظ�����ͼ��
	GL_MIRRORED_REPEAT	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	GL_CLAMP_TO_EDGE	��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*
	���˷�ʽ	����
	GL_NEAREST_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
	GL_LINEAR_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
	GL_NEAREST_MIPMAP_LINEAR	��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
	GL_LINEAR_MIPMAP_LINEAR		�������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��ǰ�������ͼƬ��������һ������
	glTexImage2D(
		GL_TEXTURE_2D, //����Ŀ��
		0, //�༶��Զ����ļ���0Ϊ��������
		bTransparency ? GL_RGBA : GL_RGB, //����������洢��ʽ
		width, //����߿�
		height, 
		0, //ֻ��Ϊ0 OpenGL��������
		bTransparency ? GL_RGBA : GL_RGB, //ԭͼ�ĸ�ʽ����������
		GL_UNSIGNED_BYTE, 
		data);//��������
	glGenerateMipmap(GL_TEXTURE_2D);

	//�ͷ�����
	stbi_image_free(data);
	return texture;
}

int CUseShaderFile::init()
{
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
	m_wnd = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);
	if (!m_wnd)
	{
		std::cout << "����ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}
	//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(m_wnd);
	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ��gladʧ��" << std::endl;
		return -1;
	}
	//ע�ᴰ�ڻص�
	glfwSetFramebufferSizeCallback(m_wnd, framebuffer_size_callback);

	//����Ψһid
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	std::cout << "wnd init finish." << std::endl;
	return 0;
}
int CUseShaderFile::texture()
{
	//����Ӧ�õ�
	float tex_vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����		
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertices), tex_vertices, GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//����stb_image���y��ʼ�ڵ�,��һ����Ƭ��y��ʼ�ڶ�,����������Ҫ����
	stbi_set_flip_vertically_on_load(true);

	m_texture = loadImage("../path/wall.jpg");
	m_texture2 = loadImage("../path/face.png", true);





	return 0;

}
int CUseShaderFile::triangle()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.0f, 0.5f, 0.0f
	};


	//���� 1,����������Ҫ�������ĵط�(VBO) 2,�����С 3,�����ַ 4,�����Կ�����ʲô��ʽ�������� GL_STATIC_DRAWΪ����ı�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//���� 1, ��Ӧ�Ķ������Ա��(location=0) 2,�������ԵĴ�С 
	//3,�������� 4,ָ���Ƿ���Ҫ�淶��(��ʱ��֪����ʲô����) 
	//5,���Կ�� ��������ÿ����Ϊһ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	return 0;
}

void CUseShaderFile::loop()
{

	CShaderFromFile shader("../path/Shader.vs", "../path/Shader.fs");

	//ѭ����Ⱦ
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

	shader.use();
	shader.setInt("ourTexture1", 0);
	shader.setInt("ourTexture2", 1);
	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		//glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);



		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

	glfwTerminate();

}
