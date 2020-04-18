#pragma once

#include <glad/glad.h>
#include <string>
#include "../include/glm/detail/func_integer.hpp"
#include "../include/glm/detail/type_mat.hpp"

class CShaderFromFile
{
public:

	CShaderFromFile( const char* vefilepath, const char* fragfilepath);
	~CShaderFromFile();


	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	void setMat4(const std::string & name, float value[]) const;

	void use();
	unsigned int GetID() const { return m_id; }
private:

	void CheckCompileErr(unsigned int ss, const std::string& str);

	unsigned int m_id;
};
