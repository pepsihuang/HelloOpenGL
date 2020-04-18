


#include "triangle.h"
#include "triangle_shader.h"
#include "CUseShaderFile.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void UseGlm()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

	//在0.9.9版本前,默认初始化为单位阵,如果是099起则是零矩阵(全部分量为0)
	glm::mat4 trans;//这里是当做变换矩阵
	//把位移量传递给矩阵,从而变成一个变换矩阵
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//把一个向量(1,0,0) 位移(1,1,0)
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



