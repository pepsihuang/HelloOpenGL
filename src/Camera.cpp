#include "Camera.h"
#include <iostream>





Camera::Camera(
	glm::vec3 pos 
	, glm::vec3 up
	, float yaw
	, float pitch)
{
	m_Position = pos;
	m_WorldUp = up;
	m_Yaw = yaw;
	m_Pitch = pitch;
	m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_MovementSpeed = SPEED;
	m_MouseSensitivity = SENSITIVITY;
	m_Zoom = ZOOM;

	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position+ m_Front, m_Up);
}

void Camera::PrecessKeyBoard(int type, float deltatime)
{
	//速率
	float velocity = m_MovementSpeed * deltatime;
	switch (type)
	{
	case _FORWARD_:
		m_Position += m_Front * velocity;
		break;
	case _BACKWARD_:
		m_Position -= m_Front * velocity;
		break;
	case _LEFT_:
		m_Position -= m_Right * velocity;
		break;
	case _RIGHT:
		m_Position += m_Right * velocity;
		break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	//重新计算 前向量 
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);

	//重新计算右向量 和 上向量

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	//标准化向量，因为他们的长度更接近于0，甚于你缓慢的上下看的结果。。。。翻译有点诡异
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
}


void Camera::ProcessMouseScroll(float offset)
{
//	if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
		m_Zoom -= offset;

// 	if (m_Zoom <= 1.0f)
// 		m_Zoom = 1.0f;
// 	if (m_Zoom >= 45.0f)
// 		m_Zoom = 45.0f;

	std::cout << "cam zoom: " << m_Zoom <<std::endl;
}