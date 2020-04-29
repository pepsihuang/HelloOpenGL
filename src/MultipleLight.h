#pragma once

#include "CBase.h"
#include "Camera.h"
#include "CShaderFromFile.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/*
����-���Դ
*/


class CMultipleLight : public CBase
{
public:
	CMultipleLight()
		:lightShader("../path/multiple_lights.vs", "../path/multiple_lights.fs")
		, lampShader("../path/lamp.vs", "../path/lamp.fs")
	{

	}
	~CMultipleLight() {}

private:


	//�ƹ����ɫ
	glm::vec3 lightPos;
	CShaderFromFile lightShader;
	CShaderFromFile lampShader;

	//���õƹ�ʹ�õ�VAO,VBO������ͬ,�ƹ����Ķ���ͬ����3d������ 
	unsigned int lightVAO;
	unsigned int diffuse_map;
	unsigned int specular_map;

	virtual void BeforeLoop()
	{
		// timing
		deltaTime = 0.0f;	// time between current frame and last frame
		lastFrame = 0.0f;
		camera.m_Position = glm::vec3(0.0f, 0.0f, 7.0f);
		firstMouse = true;
		//�ƹ��λ��
		lightPos = glm::vec3(0.3f, 1.0f, 2.0f);
		glEnable(GL_DEPTH_TEST);

		//һ��������3������,һ���ķ���6������,һ���ķ���6*6=36
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//�����������Ϣ
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//����ķ�������Ϣ
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//uv��ͼ��Ϣ
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//light
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		diffuse_map = loadImage("../path/container2.png");
		specular_map = loadImage("../path/container2_specular.png");
		lightShader.use();
		lightShader.setInt("material.diffuse", 0);
		lightShader.setInt("material.specular", 1);

	}

	

	virtual void OnLoop() {

		double curtime = glfwGetTime();
		deltaTime = curtime - lastFrame;
		lastFrame = curtime;


		//ʮ�����ӵ�λ��
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
		//���Դ��λ��
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};


		lightShader.use();
		lightShader.setVec3("viewPos", camera.m_Position);
		lightShader.setFloat("material.shininess", 32.0f);
		//ֱ���
		lightShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		//���Դ
		for (int i = 0; i < 4; ++i)
		{
			std::string str("pointLights[");
			char aa[10] = {0};
			sprintf_s(aa, "%d", i);
			str += aa;
			std::string tmp = str + "].position";
			lightShader.setVec3(tmp, pointLightPositions[i]);
			tmp = str + "].ambient";
			lightShader.setVec3(tmp, 0.05f, 0.05f, 0.05f);
			tmp = str + "].diffuse";
			lightShader.setVec3(tmp, 1.8f, 1.8f, 1.8f);
			tmp = str + "].specular";
			lightShader.setVec3(tmp, 1.0f, 1.0f, 1.0f);
			tmp = str + "].constant";
			lightShader.setFloat(tmp, 1.0f);
			tmp = str + "].linear";
			lightShader.setFloat(tmp, 0.09f);
			tmp = str + "].quadratic";
			lightShader.setFloat(tmp, 0.032f);
		}



		//�۹�
		lightShader.setVec3("spotLight.position", camera.m_Position);
		lightShader.setVec3("spotLight.direction", camera.m_Front);
		lightShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightShader.setVec3("spotLight.diffuse", 1.0f, 0.8f, 0.8f);
		lightShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightShader.setFloat("spotLight.constant", 1.0f);
		lightShader.setFloat("spotLight.linear", 0.09f);
		lightShader.setFloat("spotLight.quadratic", 0.032f);
		lightShader.setFloat("spotLight.cutOff", glm::cos(12.5f));
		lightShader.setFloat("spotLight.outerCutOff", glm::cos(15.5f));

		//�Ӿ��Լ�͸��ͶӰ�任����
		glm::mat4 projection = glm::perspective(glm::radians(camera.m_Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightShader.setMat4("projection", glm::value_ptr(projection));
		lightShader.setMat4("view", glm::value_ptr(view));
		//��������任
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.setMat4("model", glm::value_ptr(model));
		//����������ͼ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse_map);
		//�󶨾������ͼ
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular_map);
		//����10��������
		glBindVertexArray(VAO);
		for (unsigned int index = 0; index < 10; ++index)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[index]);
			float angle = 20.0f * index;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightShader.setMat4("model", glm::value_ptr(model));
			//��Ⱦ������
			glDrawArrays(GL_TRIANGLES, 0, 36);//һ��������3������,һ���ķ���6������,һ���ķ���6*6=36
		}

		//���Ƶƹ�������
		lampShader.use();
		lampShader.setMat4("projection", glm::value_ptr(projection));
		lampShader.setMat4("view", glm::value_ptr(view));
		for (unsigned int index = 0; index < 4; ++index)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[index]);
			model = glm::scale(model, glm::vec3(0.2f));//��Сһ��
			lampShader.setMat4("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);//һ��������3������,һ���ķ���6������,һ���ķ���6*6=36
		}

	}
};
