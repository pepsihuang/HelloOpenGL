#pragma once
#include "CBase.h"


class DepthTest : public CBase {
public:
	DepthTest() {

	}
	~DepthTest(){}

	CShaderFromFile mShader("../path/depthtest.vs", "../path/depthtest.fs");
	virtual void BeforeLoop()
	{
		glEnable(GL_DEPTH_TEST);
		//1.学习让所有深度测试都通过
		glDepthFunc(GL_ALWAYS);
	}

	virtual void Loop()
	{

	}
};