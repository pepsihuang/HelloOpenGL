#pragma once

#include <glad/glad.h>//需要在glfw前 否则会报编译错误
#include <glfw/glfw3.h>
#include <iostream>
#include "CShaderFromFile.h"


class CUseShaderFile {
public:
	CUseShaderFile();
	~CUseShaderFile();

	unsigned int loadImage(const char* path, bool bTransparency = false);
	int init();
	int texture();
	int triangle();
	
	int texture_3d();

	void loop();
	void loop_texture();
	void loop_texture_3d();
	//多个旋转立方体
	void loop_texture_3ds();
	//使用键盘操作移动相机
	void loop_key_move_cam();

	void UseMat4(const CShaderFromFile* shader);
	void UseMat4_move(const CShaderFromFile* shader);
private:

	static void framebuffer_size_callback1(GLFWwindow*  wnd, int width, int height);
	void processInput1(GLFWwindow* wnd);
	static void mouse_callback1(GLFWwindow* wnd, double xpos, double ypos);
	

	void exit();
	void print(const std::string& str, const glm::vec3& vec);


	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	GLFWwindow* m_wnd;
	unsigned int m_texture; //纹理唯一ID
	unsigned int m_texture2; //纹理唯一ID

	CShaderFromFile* m_shader;

	float m_cur_mix;


	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	//当前帧与上一帧的时间差
	float m_deltaTime;
	//上一帧的结束时间
	float m_lastTime;
	//使用每帧时间差来进行统一化速度,避免不同性能电脑导致帧率不同而移动速度不同
	//我们使得在固定的时间长度下,移动的速度是相同的

	//加入鼠标移动相机的俯仰角和偏航角
private:
	//是否首次鼠标进入
	bool m_first_mouse;

	double m_lastX;
	double m_lastY;
	float m_yaw;
	float m_pitch;



	//static CUseShaderFile* m_ins;
};