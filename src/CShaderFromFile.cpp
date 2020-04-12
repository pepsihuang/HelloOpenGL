#include "CShaderFromFile.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>



CShaderFromFile::CShaderFromFile(ShaderType type, const char* filepath)
	: m_id(0)
	, m_type(type)
{

	if (!filepath)
	{
		std::cout << "FILEPATH ERROR!" << std::endl;
		return;
	}

	std::string code;
	std::ifstream strfile;
	//strfile.execptions();

	try {
		strfile.open(filepath);
		std::stringstream stream;
		stream << strfile.rdbuf();
		strfile.close();
		code = stream.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cout << " FILE OPEN FAILED!" << std::endl;
	}
	const char* char_code = code.c_str();
	unsigned int ss;

	switch (type)
	{
	case _ST_Vertex_:
	{
		ss = glCreateShader(GL_VERTEX_SHADER);
		break;
	}
	case _ST_Fragment_:
	{
		ss = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	}
	glShaderSource(ss, 1, &char_code, NULL);
	glCompileShader(ss);
	CheckCompileErr(ss, false);
	m_id = glCreateProgram();
	glAttachShader(m_id, ss);
	glLinkProgram(m_id);
	CheckCompileErr(m_id, true);


}


CShaderFromFile::~CShaderFromFile()
{
}


void CShaderFromFile::CheckCompileErr(unsigned int ss, bool isProgramm)
{
	int success = 0;
	char infoLog[512] = { 0 };
	if (isProgramm)
	{
		glGetProgramiv(ss, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ss, 512, NULL, infoLog);
			std::cout << "Link Program shader FAILED!\n" << infoLog << std::endl;
		}
	} 
	else
	{
		switch (m_type)
		{
		case _ST_Vertex_:
			glGetShaderiv(ss, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(ss, 512, NULL, infoLog);
				std::cout << "complie vertex shader FAILED!\n" << infoLog << std::endl;
			}
			break;
		case _ST_Fragment_:
			glGetShaderiv(ss, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(ss, 512, NULL, infoLog);
				std::cout << "compile fragment shader FAILED!\n" << infoLog << std::endl;
			}

			break;
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




