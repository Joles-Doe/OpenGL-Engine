#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

/// <summary>
/// ShaderProgram - Object responsible for handling the OpenGL shader sent to the GPU.
/// </summary>
class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string& _vertexPath, const std::string& _fragPath);
	~ShaderProgram();

	/// <summary>
	/// Makes this object the active shader. All objects drawn after this point will follow this shader, unless SetActive is called again.
	/// </summary>
	void SetActive();

	/// <summary>
	/// Returns the ID of the compiled shader program.
	/// </summary>
	/// <returns> The OpenGL shader program ID </returns>
	GLuint ID();

	/// <summary>
	/// Changes the value of a set uniform located within the shader.
	/// </summary>
	/// <param name="_name"> Uniform variable name </param>
	/// <param name="_value"> Value to set </param>
	void SetUniform(const std::string& _name, glm::mat4 _value);

	/// <summary>
	/// Changes the value of a set uniform located within the shader.
	/// </summary>
	/// <param name="_name"> Uniform variable name </param>
	/// <param name="_value"> Value to set </param>
	void SetUniform(const std::string& _name, glm::vec4 _value);

	/// <summary>
	/// Changes the value of a set uniform located within the shader.
	/// </summary>
	/// <param name="_name"> Uniform variable name </param>
	/// <param name="_value"> Value to set </param>
	void SetUniform(const std::string& _name, glm::vec3 _value);
	
	/// <summary>
	/// Changes the value of a set uniform located within the shader.
	/// </summary>
	/// <param name="_name"> Uniform variable name </param>
	/// <param name="_value"> Value to set </param>
	void SetUniform(const std::string& _name, glm::vec2 _value);

	/// <summary>
	/// Changes the value of a set uniform located within the shader.
	/// </summary>
	/// <param name="_name"> Uniform variable name </param>
	/// <param name="_value"> Value to set </param>
	void SetUniform(const std::string& _name, float _value);
	
	/// <summary>
	/// Used in conjuntion with the ShaderStore. Doesn't do anything when called.
	/// </summary>
	void SetUniform(const std::string& _name, std::monostate) {};
private:
	/// <summary>
	/// Loads and compiles the given vertex and fragment shaders.
	/// </summary>
	/// <param name="_vertexPath"> Vertex shader path </param>
	/// <param name="_fragPath"> Fragment shader path </param>
	void LoadProgram(const std::string& _vertexPath, const std::string& _fragPath);

	GLuint mID;
};