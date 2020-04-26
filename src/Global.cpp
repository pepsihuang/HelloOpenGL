#include "Global.h"
#include "CColor.h"
#include "Material.h"

static CBase* base = NULL;

CBase* GetPtr()
{
	if (!base)
	{
		base = new CMaterial;
	}
	return base;
}
void DeletePtr()
{
	if (base)
	{
		delete base;
	}
}

void framebuffer_size_callback(GLFWwindow* wnd, int width, int height)
{
	glViewport(0, 0, width, height);//调整视窗区域
}

void mouse_callback(GLFWwindow* wnd, double xpos, double ypos)
{
	GetPtr()->OnMouseCallBack(wnd, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	GetPtr()->OnScrollCallBack(window, xoffset, yoffset);
}

