#pragma once


#include "CBase.h"
/*
用于存放全局单例
*/


CBase* GetPtr();
void framebuffer_size_callback(GLFWwindow*  wnd, int width, int height);
void mouse_callback(GLFWwindow* wnd, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

