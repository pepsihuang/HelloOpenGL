#include "CBase.h"
#include "Global.h"


CBase::CBase()
{
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
	init();
}


CBase::~CBase()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}


int CBase::init()
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
	glfwSetFramebufferSizeCallback(m_wnd, ::framebuffer_size_callback);
	glfwSetCursorPosCallback(m_wnd, ::mouse_callback);
	glfwSetScrollCallback(m_wnd, ::scroll_callback);

	//��׽���
	glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

void CBase::Loop()
{
	// timing
	deltaTime = 0.0f;	// time between current frame and last frame
	lastFrame = 0.0f;
	firstMouse = true;
	glEnable(GL_DEPTH_TEST);
	//����ǰ�ò�������ʵ��
	BeforeLoop();
	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(m_wnd))
	{

		double curtime = glfwGetTime();
		deltaTime = curtime - lastFrame;
		lastFrame = curtime;
		processInput(m_wnd);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ͬʱ�����Ȼ���
		//�����Լ�ȥʵ��
		OnLoop();

		glfwSwapBuffers(m_wnd);
		glfwPollEvents();
	}
}



void CBase::OnMouseCallBack(GLFWwindow* wnd, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void CBase::OnScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void CBase::processInput(GLFWwindow* wnd)
{

	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(wnd, true);
	else if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)//��ǰ���ƶ���: front����z��������ֵ,����ֱ�ӳ����ƶ�������
	{
		camera.PrecessKeyBoard(Camera::_FORWARD_, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.PrecessKeyBoard(Camera::_BACKWARD_, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.PrecessKeyBoard(Camera::_LEFT_, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.PrecessKeyBoard(Camera::_RIGHT_, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_Z) == GLFW_PRESS)
	{
		camera.PrecessKeyBoard(Camera::_UP_, deltaTime);
	}
	else if (glfwGetKey(wnd, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera.PrecessKeyBoard(Camera::_DOWN_, deltaTime);
	}
	else
		OnProcessInput(wnd);
}
