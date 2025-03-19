#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string& _vertexPath, const std::string& _fragPath);
	~ShaderProgram();

	void SetActive();
	GLuint ID();

	void SetUniform(const std::string& _name, glm::mat4 _value);
	void SetUniform(const std::string& _name, glm::vec4 _value);
	void SetUniform(const std::string& _name, glm::vec3 _value);
	void SetUniform(const std::string& _name, float _value);
private:
	void LoadProgram(const std::string& _vertexPath, const std::string& _fragPath);

	GLuint mID;
};