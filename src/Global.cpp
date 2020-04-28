#include "Global.h"
#include "CColor.h"
#include "Material.h"
#include "LightMaterial.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "LightCasters.h"

static CBase* base = NULL;

CBase* GetPtr()
{
	if (!base)
	{
		base = new CLightCasters;
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

unsigned int loadImage(const char* path)
{
	if (!path)
	{
		std::cout << "::loadImage: image path ERR!" << std::endl;
		return 0;
	}
	int width, height, nrChannels;//最后为颜色通道的个数
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "::loadImage: FAILED to load texture:" << path << std::endl;
		return 0;
	}
	GLenum format;
	if (nrChannels == 1)
	{
		format = GL_RED;
	}
	else if (nrChannels == 3)
	{
		format = GL_RGB;
	}
	else if (nrChannels == 4)
	{
		format = GL_RGBA;
	}
	unsigned int texture;
	//参数一 为生成纹理的数量
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//为当前绑定的纹理对象设置环绕,过滤方式
	/*
	环绕方式	描述
	GL_REPEAT	对纹理的默认行为。重复纹理图像。
	GL_MIRRORED_REPEAT	和GL_REPEAT一样，但每次重复图片是镜像放置的。
	GL_CLAMP_TO_EDGE	纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	GL_CLAMP_TO_BORDER	超出的坐标为用户指定的边缘颜色。
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*
	过滤方式	描述
	GL_NEAREST_MIPMAP_NEAREST	使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
	GL_LINEAR_MIPMAP_NEAREST	使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
	GL_NEAREST_MIPMAP_LINEAR	在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
	GL_LINEAR_MIPMAP_LINEAR		在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//把前面载入的图片数据生成一个纹理
	glTexImage2D(
		GL_TEXTURE_2D, //纹理目标
		0, //多级渐远纹理的级别，0为基础级别
		format,
		width, //纹理高宽
		height,
		0, //只能为0 OpenGL辣鸡代码
		format,
		GL_UNSIGNED_BYTE,
		data);//参数数据
	glGenerateMipmap(GL_TEXTURE_2D);

	//释放纹理
	stbi_image_free(data);

	//由于stb_image库的y起始在底,而一般照片的y起始在顶,所以我们需要修正
	stbi_set_flip_vertically_on_load(true);
	return texture;
}

