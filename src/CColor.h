#pragma once
#include "CBase.h"
#include "Camera.h"
#include "CShaderFromFile.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/*
����-��ɫ
�����ʵ�� ʵ��ֻ�ǻ���������������,Ȼ�������������ָ����ɫ
��һ���ٻ�ɫ������:
��ʹ��ɺ���� �� ��ɫ��ϴӶ�ģ������巴����ɫ��ԭ��.������ʵ�����а�ɫ������κ���ɫ�����Ϸ�������ľ������岻���յ���ɫ
��:�������ģ����ʵ���շ���Ч��

�ڶ�������ɫ������:
ģ���Դ�����,�����������������Ȿ��,������ʵ�����еĵ���/̫��

����ɫ�����嵥������һ����ɫ����Ŀ����Ϊ�˸�������������ɫ,�Ӷ����������޸����屾����ɫʱ ���ְ�ɫ������(��Դ)�Ķ���.
������lamp.fs�оͺܼ򵥵�д����ȫ��1.0�����İ�ɫ.


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

	//�ƹ����ɫ
	glm::vec3 lightPos;
	CShaderFromFile lightShader;
	CShaderFromFile lampShader;

	//���õƹ�ʹ�õ�VAO,VBO������ͬ,�ƹ����Ķ���ͬ����3d������ 
	unsigned int lightVAO;

	virtual void BeforeLoop() 
	{
		// timing
		deltaTime = 0.0f;	// time between current frame and last frame
		lastFrame = 0.0f;
		camera.m_Position = glm::vec3(0.0f, 0.0f, 7.0f);
		firstMouse = true;
		//�ƹ��λ��
		lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		glEnable(GL_DEPTH_TEST);

		//һ��������3������,һ���ķ���6������,һ���ķ���6*6=36
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
		//�����������Ϣ
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//����ķ�������Ϣ
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
		//������Ʒ����ɫ�͵ƹ����ɫ
		lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);//���������Ҫ����ѭ������,������޷���ʾ��

		//�Ӿ��Լ�͸��ͶӰ�任����
		glm::mat4 projection = glm::perspective(glm::radians(camera.m_Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightShader.setMat4("projection", glm::value_ptr(projection));
		lightShader.setMat4("view", glm::value_ptr(view));
	
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.setMat4("model", glm::value_ptr(model));

		//��Ⱦ������
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);//һ��������3������,һ���ķ���6������,һ���ķ���6*6=36
	
		//���Ƶƹ�������
		lampShader.use();
		lampShader.setMat4("projection", glm::value_ptr(projection));
		lampShader.setMat4("view", glm::value_ptr(view));
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));//��Сһ��
		lampShader.setMat4("model", glm::value_ptr(model));

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


	}

	virtual void OnProcessInput(GLFWwindow* wnd) 
	{

		//��ǰ���ƶ���: front����z��������ֵ,����ֱ�ӳ����ƶ�������
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
