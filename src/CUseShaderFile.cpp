#include "CUseShaderFile.h"
#include "CShaderFromFile.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

CUseShaderFile * m_ins;

void CUseShaderFile::framebuffer_size_callback1(GLFWwindow* wnd, int width, int height)
{
	glViewport(0, 0, width, height);//�����Ӵ�����
}

void CUseShaderFile::processInput1(GLFWwindow* wnd)
{

	float cameraSpeed = 0.5f * m_deltaTime;//�������
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(wnd, true);
	else if (glfwGetKey(wnd, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_cur_mix -= 0.1f;
		m_shader->setFloat("va_mix", m_cur_mix);
		std::cout << m_cur_mix << std::endl;

	}
	else if (glfwGetKey(wnd, GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_cur_mix += 0.1f;
		m_shader->setFloat("va_mix", m_cur_mix);
		std::cout << m_cur_mix << std::endl;

	}
	//��ǰ���ƶ���: front����z��������ֵ,����ֱ�ӳ����ƶ�������
	else if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
		print("cam", cameraPos);

	}
	else if (glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
		print("cam", cameraPos);

	}
	//�������ƶ���: ʹ�ò�˻��һ��������,��������������ƶ�,�Ӷ���ú����ƶ���Ч��
	//����ʹ��normalize��׼������,��Ϊ���ƶ�������ٵ�
	else if (glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
		print("cam", cameraPos);

	}
	else if (glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
		print("cam", cameraPos);
	}
	//�Լ������޸�Y����,(����)
	else if (glfwGetKey(wnd, GLFW_KEY_Z) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraUp;
		print("cam", cameraPos);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_C) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraUp;
		print("cam", cameraPos);
	}

}

void CUseShaderFile::mouse_callback1(GLFWwindow* wnd, double xpos, double ypos)
{
	
	if (m_ins->m_first_mouse)
	{
		//m_ins->m_lastX = xpos;
		//m_ins->m_lastY = ypos;
		m_ins->m_first_mouse = false;
		std::cout << "mouse begin..." << std::endl;
	}

	float xoffset = xpos - m_ins->m_lastX;
	float yoffset = m_ins->m_lastY - ypos;
	m_ins->m_lastX = xpos;
	m_ins->m_lastY = ypos;

	float sensitivity = 0.03f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	m_ins->m_yaw += xoffset;
	m_ins->m_pitch += yoffset;

	if (m_ins->m_pitch > 89.0f)
		m_ins->m_pitch = 89.0f;
	if (m_ins->m_pitch < -89.0f)
		m_ins->m_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_ins->m_yaw)) * cos(glm::radians(m_ins->m_pitch));
	front.y = sin(glm::radians(m_ins->m_pitch));
	front.z = sin(glm::radians(m_ins->m_yaw)) * cos(glm::radians(m_ins->m_pitch));
	m_ins->cameraFront = glm::normalize(front);

}

void CUseShaderFile::exit()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate();
}

void CUseShaderFile::print(const std::string& str, const glm::vec3& vec)
{
	std::cout << str << " " << vec.x << " " << vec.y << " " << vec.z << std::endl;
}

CUseShaderFile::CUseShaderFile() 
	: m_wnd(NULL)
	, m_cur_mix(0.2f)
	, m_deltaTime(0.0f)
	, m_lastTime(0.0f)
	, m_first_mouse(true)
	, m_lastX((float)SCR_WIDTH  / 2)
	, m_lastY((float)SCR_HEIGHT / 2)
	, m_pitch(0.0f)
	, m_yaw(0.0f)
{
	init();
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);//���λ��
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);//����ķ������� (���λ��+��������=Ŀ��λ��)
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//���������
	m_ins = this;
}

CUseShaderFile::~CUseShaderFile()
{

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
	glfwSetFramebufferSizeCallback(m_wnd, framebuffer_size_callback1);



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

int CUseShaderFile::texture_3d()
{

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//����stb_image���y��ʼ�ڵ�,��һ����Ƭ��y��ʼ�ڶ�,����������Ҫ����
	stbi_set_flip_vertically_on_load(true);

	m_texture = loadImage("../path/wall.jpg");
	m_texture2 = loadImage("../path/face.png", true);


	return 0;
}

void CUseShaderFile::loop()
{
	m_shader = new CShaderFromFile("../path/Shader.vs", "../path/Shader.fs");


	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput1(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		m_shader->use();
		double timeValue = glfwGetTime();
		double Value = (sin(timeValue) / 2.0f);
		m_shader->setFloat("xoffset", (float)Value);

		//glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}
	exit();
}

void CUseShaderFile::loop_texture()
{
	m_shader = new CShaderFromFile("../path/mat4_shader.vs", "../path/tex_shader.fs");
	
	m_shader->use();
	m_shader->setInt("ourTexture1", 0);
	m_shader->setInt("ourTexture2", 1);

	m_shader->setFloat("va_mix", m_cur_mix);

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput1(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//

		//glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);


		//UseMat4(m_shader);
		UseMat4_move(m_shader);
		m_shader->use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

	exit();

}


void CUseShaderFile::loop_texture_3d()
{
	texture_3d();
	m_shader = new CShaderFromFile("../path/3d_shader.vs", "../path/3d_shader.fs");

	m_shader->use();
	m_shader->setInt("texture1", 0);
	m_shader->setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput1(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ͬʱ�����Ȼ���

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);


		m_shader->use();
		
		//�����任����
		glm::mat4 model      = glm::mat4(1.0f);
		glm::mat4 view       = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		
		model      = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//�Ƕ�Ϊ45�ȡ�
		//�ڶ���������������Ļ��߱ȣ�aspect ratio�������ֵ��Ӱ����ʾ�������е�������ԭ����ʾ���Ǳ����졣
		//0.1f�ǽ��ü��棬
		//100.0f��Զ�ü��档
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(m_shader->GetID(), "model");
		unsigned int viewLoc  = glGetUniformLocation(m_shader->GetID(), "view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		//m_shader->setMat4("projection", projection);//�ٷ���������������� ���ݲ����������.��ʱʹ�ñ�ķ���
		m_shader->setMat4("projection", glm::value_ptr(projection));

		glBindVertexArray(VAO);
		//����������
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}
}




void CUseShaderFile::loop_texture_3ds()
{
	texture_3d();
	m_shader = new CShaderFromFile("../path/3d_shader.vs", "../path/3d_shader.fs");

	m_shader->use();
	m_shader->setInt("texture1", 0);
	m_shader->setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);

	//ʮ��������
	glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),

	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput1(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ͬʱ�����Ȼ���

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);


		m_shader->use();

		m_shader->setMat4("projection", glm::value_ptr(projection));

		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);

			float angle = 20.0f *i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			m_shader->setMat4("model", glm::value_ptr(model));
			//����������
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//Բ�İ뾶
		float radius = 5.0f;
		float camX = sin(glfwGetTime()) * radius;//
		float camZ = cos(glfwGetTime()) * radius;//
		std::cout <<"time: "<< glfwGetTime() << "camx: " << camX << " camz: " << camZ << std::endl;
		glm::mat4 view;
		//
		view = glm::lookAt(
			glm::vec3(camX, 0.0f, camZ), //���λ��
			glm::vec3(0.0f, 0.0f, 0.0f), //Ŀ��λ��
			glm::vec3(0.0f, 1.0f, 0.0f));//������

		m_shader->setMat4("view", glm::value_ptr(view));

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

}




void CUseShaderFile::loop_key_move_cam()
{

	//ע������ƶ��Ļص�
	glfwSetCursorPosCallback(m_wnd, mouse_callback1);
	//��������ָ����
	glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	float curTime = glfwGetTime();
	m_deltaTime = curTime - m_lastTime;
	m_lastTime = curTime;
	texture_3d();
	m_shader = new CShaderFromFile("../path/3d_shader.vs", "../path/3d_shader.fs");

	m_shader->use();
	m_shader->setInt("texture1", 0);
	m_shader->setInt("texture2", 1);

	glEnable(GL_DEPTH_TEST);

	//ʮ��������
	glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),

	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{
		processInput1(m_wnd);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ͬʱ�����Ȼ���

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);


		m_shader->use();

		m_shader->setMat4("projection", glm::value_ptr(projection));

		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);

			float angle = 20.0f *i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			m_shader->setMat4("model", glm::value_ptr(model));
			//����������
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		view = glm::lookAt(
			cameraPos, //���λ��
			cameraPos + cameraFront, //Ŀ��λ��
			cameraUp);//������

		m_shader->setMat4("view", glm::value_ptr(view));

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}

}

void CUseShaderFile::UseMat4(const CShaderFromFile* shader)
{
	if (!shader)
		return;
	
	glm::mat4 trans;

	//����ͼ��ת90�� (glm::radiansΪ���Ƕ�ת��Ϊ����)
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//����ͼ���ԭ����һ���
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	
	unsigned int transformLoc = glGetUniformLocation(shader->GetID(), "transform");
	//����:
	//1.����uniform��λ��ֵ
	//2.����OpenGL���ǽ����Ͷ��ٸ�����,����Ϊ1��
	//3.Ϊ�Ƿ�ϣ�������ǵľ�������û�(�Ƿ���Ҫ���������к���),OpenGL�ڲ����󲼾ֽ� ������.glmҲ��ͬ.���Ա���
	//4.�����ľ������.
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



}

void CUseShaderFile::UseMat4_move(const CShaderFromFile * shader)
{
	if (!shader)
		return;

	glm::mat4 trans;
	//ͬ�������ǵ�λ��Ȼ�����λ��(0.5, -0.5, 0)
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	//��ͼ������ʱ����̶���ת
	//(����gettime�������ص��ǵ�ǰ���е�����,��������ô���������ת����Ļ��ȵ�?�����ڱ�������ѭ����
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	unsigned int transformLoc = glGetUniformLocation(shader->GetID(), "transform");
	//����:
	//1.����uniform��λ��ֵ
	//2.����OpenGL���ǽ����Ͷ��ٸ�����,����Ϊ1��
	//3.Ϊ�Ƿ�ϣ�������ǵľ�������û�(�Ƿ���Ҫ���������к���),OpenGL�ڲ����󲼾ֽ� ������.glmҲ��ͬ.���Ա���
	//4.�����ľ������.
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


}
