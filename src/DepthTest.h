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
		//1.ѧϰ��������Ȳ��Զ�ͨ��
		glDepthFunc(GL_ALWAYS);
	}

	virtual void Loop()
	{

	}
};