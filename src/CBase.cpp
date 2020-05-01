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
	glfwSetFramebufferSizeCallback(m_wnd, ::framebuffer_size_callback);
	glfwSetCursorPosCallback(m_wnd, ::mouse_callback);
	glfwSetScrollCallback(m_wnd, ::scroll_callback);

	//捕捉鼠标
	glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//生成唯一id
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
	//如有前置操作自行实现
	BeforeLoop();
	//循环渲染
	while (!glfwWindowShouldClose(m_wnd))
	{

		double curtime = glfwGetTime();
		deltaTime = curtime - lastFrame;
		lastFrame = curtime;
		processInput(m_wnd);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//同时清除深度缓存
		//子类自己去实现
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
	else if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)//在前后移动中: front中是z方向有数值,所以直接乘上移动量即可
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
