#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.h"

/// <summary>
/// ShaderStore - centralised location for each Shader's specific uniforms. Allows the user to add their own uniforms.
/// </summary>
class ShaderStore
{
public:
	/// <summary>
	/// Base value enum. Used in the constructor - dictates which default values populate the store.
	/// </summary>
	enum BASE_VALUES
	{
		TWO_DIMENSION,
		THREE_DIMENSION,
		EMPTY
	};

	ShaderStore(BASE_VALUES _template);

	void AddUniform(const std::string& _name);

	void ChangeUniform(const std::string& _name, glm::mat4 _value);
	void ChangeUniform(const std::string& _name, glm::vec4 _value);
	void ChangeUniform(const std::string& _name, glm::vec3 _value);
	void ChangeUniform(const std::string& _name, glm::vec2 _value);
	void ChangeUniform(const std::string& _name, float _value);

	bool UniformExists(const std::string& _key);

	void UpdateShaderUniforms(std::shared_ptr<ShaderProgram> _shader);
private:
	// Prevent empty default constructor from being called
	ShaderStore();

	

	using mMapValues = std::variant<glm::mat4, glm::vec4, glm::vec3, glm::vec2, float, std::monostate>;
	
	std::unordered_map<std::string, mMapValues> mUniformMap;
};