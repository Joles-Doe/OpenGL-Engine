#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	LoadProgram("./data/shaders/GenericVS.vs", "./data/shaders/GenericFS.fs");
}

ShaderProgram::ShaderProgram(const std::string& _vertexPath, const std::string& _fragPath) : mID(0)
{
	LoadProgram(_vertexPath, _fragPath);
}

ShaderProgram::~ShaderProgram()
{
	if (mID)
	{
		glDeleteProgram(mID);
	}
}

void ShaderProgram::LoadProgram(const std::string& _vertexPath, const std::string& _fragPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	try
	{
		vertexFile.open(_vertexPath);
		fragmentFile.open(_fragPath);

		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("Shader File read error");
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	mSource = fragmentCode;

	/*const char* vertexShaderCode =
		"attribute vec3 aPosition;" \
		"attribute vec2 aPixelColor;" \
		"" \
		"varying vec2 vTextureCoord;" \
		"" \
		"uniform mat4 uProjection;" \
		"uniform mat4 uView;" \
		"uniform mat4 uModel;" \
		"" \
		"void main()" \
		"{" \
		"	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);" \
		"	vTextureCoord = aPixelColor;" \
		"}";

	const char* fragmentShaderCode = 
		"uniform sampler2D uTexture;" \
		"" \
		"varying vec2 vTextureCoord;" \
		"" \
		"void main()" \
		"{" \
		"	vec4 tex = texture2D(uTexture, vTextureCoord);" \
		"	gl_FragColor = tex;" \
		"}";*/

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);

	GLint success = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Vertex Shader compile error");
	}

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Fragment Shader compile error");
	}

	mID = glCreateProgram();
	glAttachShader(mID, vertexShaderID);
	glAttachShader(mID, fragmentShaderID);

	glBindAttribLocation(mID, 0, "aPosition");
	glBindAttribLocation(mID, 1, "aPixelColor");
	glBindAttribLocation(mID, 2, "aNormal");

	glLinkProgram(mID);
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Shader link error");
	}

	glDetachShader(mID, vertexShaderID);
	glDetachShader(mID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void ShaderProgram::SetActive()
{
	glUseProgram(ID());
}

GLuint ShaderProgram::ID()
{
	return mID;
}

void ShaderProgram::SetUniform(const std::string& _name, glm::mat4 _value)
{
	glUseProgram(ID());
	glUniformMatrix4fv(glGetUniformLocation(mID, _name.c_str()), 1, GL_FALSE, glm::value_ptr(_value));
}

void ShaderProgram::SetUniform(const std::string& _name, glm::vec4 _value)
{
	glUseProgram(ID());
	glUniform4fv(glGetUniformLocation(mID, _name.c_str()), 4, glm::value_ptr(_value));
}

void ShaderProgram::SetUniform(const std::string& _name, glm::vec3 _value)
{
	glUseProgram(ID());

	if (ID() != 5) return;

	printf("Setting uniform: %s\n", _name.c_str());
	GLint x = glGetUniformLocation(mID, _name.c_str());
	if (x == -1) std::cout << "uniform set failure " << std::endl;

	std::cout << mID << std::endl;
	std::cout << _value.x << std::endl;

	//glUniform3fv(x, 3, glm::value_ptr(_value));
	glUniform3f(x, _value.x, _value.y, _value.z);
}

void ShaderProgram::SetUniform(const std::string& _name, float _value)
{
	glUseProgram(ID());
	glUniform1f(glGetUniformLocation(mID, _name.c_str()), _value);
}