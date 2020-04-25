#pragma once



#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f)
	, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)
		, float yaw = YAW
		, float pitch = PITCH
		);
	~Camera();


	enum {
		_FORWARD_,
		_BACKWARD_,
		_LEFT_,
		_RIGHT_,
		_UP_,
		_DOWN_,
	};
	// 获得lookat变换矩阵
	glm::mat4 GetViewMatrix();
	// 根据键盘操作移动镜头
	void PrecessKeyBoard(int type, float deltatime);
	//根据鼠标移动设置俯仰角以及偏航角
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

	void ProcessMouseScroll(float offset);

	void updateCameraVectors();
	//相机属性
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	//欧拉角
	float     m_Yaw;//偏航角
	float     m_Pitch;//俯仰角
	//相机参数
	float     m_MovementSpeed;
	float     m_MouseSensitivity;
	float     m_Zoom;
};

