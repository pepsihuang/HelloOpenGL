#pragma once

#include "CBase.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "CShaderFromFile.h"
#include "model.h"

/*
使用model进行加载模型并展示
*/


class CUseModel : public CBase
{
public:
	CUseModel()
		:mShader("../path/model_loading.vs", "../path/model_loading.fs")
		, mModel(NULL)
	{
	}
	~CUseModel() 
	{
		if (mModel)
			delete mModel;
	}

private:


	CShaderFromFile mShader;
	Model * mModel;

	virtual void BeforeLoop()
	{

		camera.m_Position = glm::vec3(0.0f, 0.0f, 7.0f);
		mModel = new Model("../path/nanosuit/nanosuit.obj");

	}


	virtual void OnLoop() {


		mShader.use();

		//视觉以及透视投影变换矩阵
		glm::mat4 projection = glm::perspective(glm::radians(camera.m_Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		mShader.setMat4("projection", glm::value_ptr(projection));
		mShader.setMat4("view", glm::value_ptr(view));


		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));//缩小一点
		mShader.setMat4("model", glm::value_ptr(model));
		mModel->Draw(mShader);

	}

};
