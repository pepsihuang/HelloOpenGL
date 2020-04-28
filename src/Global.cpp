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
	glViewport(0, 0, width, height);//�����Ӵ�����
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
	int width, height, nrChannels;//���Ϊ��ɫͨ���ĸ���
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
	//����һ Ϊ�������������
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//Ϊ��ǰ�󶨵�����������û���,���˷�ʽ
	/*
	���Ʒ�ʽ	����
	GL_REPEAT	�������Ĭ����Ϊ���ظ�����ͼ��
	GL_MIRRORED_REPEAT	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	GL_CLAMP_TO_EDGE	��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*
	���˷�ʽ	����
	GL_NEAREST_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
	GL_LINEAR_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
	GL_NEAREST_MIPMAP_LINEAR	��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
	GL_LINEAR_MIPMAP_LINEAR		�������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��ǰ�������ͼƬ��������һ������
	glTexImage2D(
		GL_TEXTURE_2D, //����Ŀ��
		0, //�༶��Զ����ļ���0Ϊ��������
		format,
		width, //����߿�
		height,
		0, //ֻ��Ϊ0 OpenGL��������
		format,
		GL_UNSIGNED_BYTE,
		data);//��������
	glGenerateMipmap(GL_TEXTURE_2D);

	//�ͷ�����
	stbi_image_free(data);

	//����stb_image���y��ʼ�ڵ�,��һ����Ƭ��y��ʼ�ڶ�,����������Ҫ����
	stbi_set_flip_vertically_on_load(true);
	return texture;
}

