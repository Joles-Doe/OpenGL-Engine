#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Model.h"
#include "Texture.h"
//#include <stb_image.h>

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{

	SDL_Window* window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Connect to graphics card

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("No context");
	}

	//can't init glew without connection to graphics card
	//Glew loads OpenGL and extensions at runtime

	int x = glewInit();

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	// ================================================================================================ //
	
	Model testModel = Model("TestSkull/Skull.obj");

	Texture testTexture = Texture("TestSkull/Skull.jpg");
	
	// ================================================================================================ //

	const GLchar* vertexShaderSrc =
		"attribute vec3 a_Position;            " \
		"attribute vec2 a_TexCoord;               " \
		"                                       " \
		"varying vec2 v_TexCoord;                 " \
		"                                       " \
		"uniform mat4 u_Projection;" \
		"uniform mat4 u_Model;" \
		"                                       " \
		"void main()                            " \
		"{                                      " \
		" gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0); " \
		" v_TexCoord = a_TexCoord;                  " \
		"}                                      " \
		"                                       ";

	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Error while making the vertex shader");
	}

	const GLchar* fragmentShaderSrc =
		"uniform sampler2D u_Texture;   " \
		"                          " \
		"varying vec2 v_TexCoord;" \
		"void main()               " \
		"{                         " \
		" vec4 tex = texture2D(u_Texture, v_TexCoord); " \
		" gl_FragColor = tex; " \
		"}                         " \
		"                          ";

	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// ================================================================================================ //

	// Create new shader program and attach our shader objects
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(programId, 0, "a_Position");

	//Bind color to second position
	glBindAttribLocation(programId, 1, "a_TexCoord");

	// Perform the link and check for failure
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}


	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	// Find uniform locations
	GLint modelLoc = glGetUniformLocation(programId, "u_Model");
	GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");

	// ================================================================================================ //

	float angle{ 0 };
	int width = 0;
	int height = 0;

	bool quit = false;
	while (!quit)
	{
		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		SDL_Event e{ 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);

		// Prepare the model matrix
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -2.5f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

		// Increase the float angle so next frame the triangle rotates further
		angle += 0.5f;

		// Make sure the current program is bound
		//Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(testModel.VaoID());
		glBindTexture(GL_TEXTURE_2D, testTexture.ID());

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
			glm::value_ptr(projection));

		// Draw shape as before

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw the vertices of the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Reset the state
		glUseProgram(0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Do drawing
		SDL_GL_SwapWindow(window);
	}

	return 0;
}