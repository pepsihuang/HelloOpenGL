#include "CShaderFromFile.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "../include/glad/glad.h"



CShaderFromFile::CShaderFromFile(const char* vefilepath, const char* fragfilepath)
	: m_id(0)
{

	if (!vefilepath || !fragfilepath)
	{
		std::cout << "FILEPATH ERROR!" << std::endl;
		return;
	}

	std::string codev;
	std::string codef;
	std::ifstream strfilev;
	std::ifstream strfilef;

	try {
		strfilev.open(vefilepath);
		strfilef.open(fragfilepath);
		std::stringstream streamv;
		std::stringstream streamf;
		streamv << strfilev.rdbuf();
		streamf << strfilef.rdbuf();
		strfilev.close();
		strfilef.close();
		codev = streamv.str();
		codef = streamf.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cout << " FILE OPEN FAILED! "<<e.code() << std::endl;
		return;
	}
	const char* char_codev = codev.c_str();
	const char* char_codef = codef.c_str();
	
	unsigned int ssv = glCreateShader(GL_VERTEX_SHADER);
	unsigned int ssf = glCreateShader(GL_FRAGMENT_SHADER);


	glShaderSource(ssv, 1, &char_codev, NULL);
	glShaderSource(ssf, 1, &char_codef, NULL);
	glCompileShader(ssv);
	glCompileShader(ssf);
	CheckCompileErr(ssv, "vertex");
	CheckCompileErr(ssf, "fragment");
	m_id = glCreateProgram();
	glAttachShader(m_id, ssv);
	glAttachShader(m_id, ssf);
	glLinkProgram(m_id);
	CheckCompileErr(m_id, "program");

	glDeleteShader(ssv);
	glDeleteShader(ssf);
}


CShaderFromFile::~CShaderFromFile()
{
}


void CShaderFromFile::CheckCompileErr(unsigned int ss, const std::string& str)
{
	int success = 0;
	char infoLog[512] = { 0 };
	if (str == "program")
	{
		glGetProgramiv(ss, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ss, 512, NULL, infoLog);
			std::cout <<str<< " : Link Program shader FAILED!\n" << infoLog << std::endl;
		}
	} 
	else
	{

		glGetShaderiv(ss, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ss, 512, NULL, infoLog);
			std::cout << str << " : complie shader FAILED!\n" << infoLog << std::endl;
		}

	}

}

void CShaderFromFile::use()
{
	glUseProgram(m_id);
}

void CShaderFromFile::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}
void CShaderFromFile::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void CShaderFromFile::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}



void CShaderFromFile::setMat4(const std::string& name, float value[]) const {
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, value);
}

void CShaderFromFile::setVec3(const std::string & name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void CShaderFromFile::setVec3(const std::string & name, const glm::vec3& vec)
{
	glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec[0]);
}
