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
	// ���lookat�任����
	glm::mat4 GetViewMatrix();
	// ���ݼ��̲����ƶ���ͷ
	void PrecessKeyBoard(int type, float deltatime);
	//��������ƶ����ø������Լ�ƫ����
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);

	void ProcessMouseScroll(float offset);

	void updateCameraVectors();
	//�������
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	//ŷ����
	float     m_Yaw;//ƫ����
	float     m_Pitch;//������
	//�������
	float     m_MovementSpeed;
	float     m_MouseSensitivity;
	float     m_Zoom;
};

