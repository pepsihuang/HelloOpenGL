


#include "triangle.h"
#include "triangle_shader.h"
#include "CUseShaderFile.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void UseGlm()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

	//��0.9.9�汾ǰ,Ĭ�ϳ�ʼ��Ϊ��λ��,�����099�����������(ȫ������Ϊ0)
	glm::mat4 trans;//�����ǵ����任����
	//��λ�������ݸ�����,�Ӷ����һ���任����
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//��һ������(1,0,0) λ��(1,1,0)
	vec = trans * vec;
	std::cout << vec.x<<vec.y<<vec.z << std::endl;

}

int main()
{
	//Triangle tri;
	//TriangleShader tri;

	CUseShaderFile tri;
	//tri.texture();
	//tri.loop_texture();

	//tri.triangle();
	//tri.loop();

	//UseGlm();

	tri.loop_texture_3ds();
	return 0;
}



