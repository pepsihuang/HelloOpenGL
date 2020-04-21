#pragma once


namespace HDAN_COLOR {

	#include <glad/glad.h>//需要在glfw前 否则会报编译错误
	#include <glfw/glfw3.h>
	#include <iostream>

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>

	#include "CShaderFromFile.h"
	#include "Camera.h"


	void funcmain()
	{
		CShaderFromFile shader("path/shader.vs", "path/shader.vs");
		Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
		std::cout<<"funcmain"<<std::endl;
	}

};
