#include "ShaderStore.h"

ShaderStore::ShaderStore(BASE_VALUES _template)
{
	switch (_template)
	{
	case THREE_DIMENSION:
		AddUniform("uView");
		AddUniform("uViewPos");
		AddUniform("uProjection");
		AddUniform("uModel");
		break;
	case TWO_DIMENSION:
		AddUniform("uProjection");
		AddUniform("uModel");
		AddUniform("uColor");
		break;
	default:
	case EMPTY:
		break;
	}
}

void ShaderStore::AddUniform(const std::string& _name)
{
	bool exists = UniformExists(_name);
	if (!exists)
	{
		mUniformMap.insert({_name, std::monostate()});
	}
}

void ShaderStore::ChangeUniform(const std::string& _name, glm::mat4 _value)
{
	mUniformMap[_name] = _value;
}

void ShaderStore::ChangeUniform(const std::string& _name, glm::vec4 _value)
{
	mUniformMap[_name] = _value;
}

void ShaderStore::ChangeUniform(const std::string& _name, glm::vec3 _value)
{
	mUniformMap[_name] = _value;
}

void ShaderStore::ChangeUniform(const std::string& _name, glm::vec2 _value)
{
	mUniformMap[_name] = _value;
}

void ShaderStore::ChangeUniform(const std::string& _name, float _value)
{
	mUniformMap[_name] = _value;
}

bool ShaderStore::UniformExists(const std::string& _key)
{
	auto it = mUniformMap.find(_key);
	return it != mUniformMap.end();
}

void ShaderStore::UpdateShaderUniforms(std::shared_ptr<ShaderProgram> _shader)
{
	_shader->SetActive();
	for (const auto& entry : mUniformMap)
	{
		std::visit([&](auto&& value)
			{
				if (!std::holds_alternative<std::monostate>(entry.second))
				{
					_shader->SetUniform(entry.first, value);
				}
			}, entry.second);
	}
}