#pragma once
#include "CBase.h"
#include "Camera.h"
#include "CShaderFromFile.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/*
光照-颜色
这里的实现 实际只是绘制了两个立方体,然后给两个立方体指定颜色
第一个橘黄色立方体:
是使用珊瑚红 和 白色混合从而模拟出物体反射颜色的原理.就像现实生活中白色光打在任何颜色物体上反射出来的就是物体不吸收的颜色
即:向量点乘模拟现实光照反射效果

第二个纯白色立方体:
模拟光源本身的,用这个立方体来代表光本体,就像现实生活中的灯泡/太阳

给白色立方体单独建立一个着色器的目的是为了给它单独设置颜色,从而后面再在修改物体本身颜色时 保持白色立方体(光源)的独立.
所以在lamp.fs中就很简单的写死了全是1.0向量的白色.


*/


class CColor : public CBase
{
public:
	CColor() 
		:lightShader("../path/color.vs", "../path/color.fs")
		,lampShader("../path/lamp.vs", "../path/lamp.fs")
	{
		lastX = SCR_WIDTH / 2.0f;
		lastY = SCR_HEIGHT / 2.0f;
	}
	~CColor() {}

private:
	float deltaTime;	// time between current frame and last frame
	float lastFrame;

	Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;

	//灯光的颜色
	glm::vec3 lightPos;
	CShaderFromFile lightShader;
	CShaderFromFile lampShader;

	//配置灯光使用的VAO,VBO保持相同,灯光对象的顶点同样是3d立方体 
	unsigned int lightVAO;

	virtual void BeforeLoop() 
	{
		// timing
		deltaTime = 0.0f;	// time between current frame and last frame
		lastFrame = 0.0f;
		camera.m_Position = glm::vec3(0.0f, 0.0f, 7.0f);
		firstMouse = true;
		//灯光的位置
		lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		glEnable(GL_DEPTH_TEST);

		//一个三角形3个顶点,一个四方形6个顶点,一个四方体6*6=36
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f	
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//顶点的坐标信息
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//顶点的法向量信息
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//light
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);



	}


	virtual void OnLoop() {

		double curtime = glfwGetTime();
		deltaTime = curtime - lastFrame;
		lastFrame = curtime;

		lightShader.use();
		//设置物品的颜色和灯光的颜色
		lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);//这个还是需要放在循环当中,否则就无法显示了

		//视觉以及透视投影变换矩阵
		glm::mat4 projection = glm::perspective(glm::radians(camera.m_Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightShader.setMat4("projection", glm::value_ptr(projection));
		lightShader.setMat4("view", glm::value_ptr(view));
	
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.setMat4("model", glm::value_ptr(model));

		//渲染立方体
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);//一个三角形3个顶点,一个四方形6个顶点,一个四方体6*6=36
	
		//绘制灯光立方体
		lampShader.use();
		lampShader.setMat4("projection", glm::value_ptr(projection));
		lampShader.setMat4("view", glm::value_ptr(view));
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));//缩小一点
		lampShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


	}

	virtual void OnProcessInput(GLFWwindow* wnd) 
	{

		//在前后移动中: front中是z方向有数值,所以直接乘上移动量即可
		if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)
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
			camera.PrecessKeyBoard(Camera::_RIGHT, deltaTime);
		}
	}
	virtual void OnMouseCallBack(GLFWwindow* wnd, double xpos, double ypos)
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
	virtual void OnScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(yoffset);
	
	}
};
