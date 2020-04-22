#pragma once
#include "CBase.h"
//#include "Camera.h"


class CColor : public CBase
{
public:
	CColor() {}
	~CColor() {}

private:
	virtual void BeforeLoop() 
	{
		// timing
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		// camera
		//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
		float lastX = SCR_WIDTH / 2.0f;
		float lastY = SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		float deltaTime = 0.0f;
		float lastTime = 0.0f;
		//打开深度测试
		glEnable(GL_DEPTH_TEST);

	}
	virtual void OnLoop() {

	}

	virtual void OnProcessInput(GLFWwindow* wnd) {}
	virtual void OnMouseCallBack(GLFWwindow* wnd, double xpos, double ypos) {}
	virtual void OnScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {}
};
