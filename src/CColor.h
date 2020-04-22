#pragma once
#include "CBase.h"
#include "Camera.h"
//#include "Camera.h"


class CColor : public CBase
{
public:
	CColor() 
		:lightShader("../path/color.vs", "../path/color.fs")
		,lampShader("../path/color.vs", "../path/lamp.fs")
	{}
	~CColor() {}

private:
	float deltaTime;	// time between current frame and last frame
	float lastFrame;

	Camera camera;
	const float lastX = SCR_WIDTH / 2.0f;
	const float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse;

	//灯光的颜色
	glm::vec3 lightPos;
	CShaderFromFile lightShader;
	CShaderFromFile lampShader;
	virtual void BeforeLoop() 
	{
		// timing
		deltaTime = 0.0f;	// time between current frame and last frame
		lastFrame = 0.0f;
		camera.m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		firstMouse = true;
		//灯光的颜色
		lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		glEnable(GL_DEPTH_TEST);

		float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		};



	}


	virtual void OnLoop() {

	}

	virtual void OnProcessInput(GLFWwindow* wnd) {}
	virtual void OnMouseCallBack(GLFWwindow* wnd, double xpos, double ypos) {}
	virtual void OnScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {}
};
