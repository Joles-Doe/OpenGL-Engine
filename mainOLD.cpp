#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int mainOLD()
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



	//Prepare Position VBO

	// VBO is a memory buffer in the high speed memomry of the GPU. It holds information about the vertices

	//triangle points - OpenGL vertices go counter clockwise
	//This doesn't need to include z since it's 2D but it does here
	const GLfloat positions[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	//handle to reference the VBO
	GLuint positionsVboId = 0;

	//Create a new Vertex Buffer Object on the GPU and bind it
	//Buffer Objects - store an array of unformatted memory allocated by the OpenGL context (GPU)
	//glGenBufferes creates the buffer object
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::runtime_error("Couldn't bind the VBO");
	}


	//This tells the GL_ARRAY_BUFFER that any data it gets is going to be copied into positionVboId 
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	//GL_STATIC_DRAW - static memory on the graphics card
	//GL_ARRAY_BUFFER is given the positions so it copies the vertex data into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	//Prepare Color VBO

	const GLfloat colors[] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f
	};

	GLuint colorsVboId = 0;

	// Create a colors VBO on the GPU and bind it
	glGenBuffers(1, &colorsVboId);

	if (!colorsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	// Reset the state
	//Clear GL_ARRAY_BUFFER since it doesn't need the positions data anymore
	//since positionsVboId has it now
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Prepare VAO
	//VAOs contain VBOs. Designed to store info about the complete rendered object
	//So it stores each VBO(vertex) of the triangle

	//handle to reference the VAO
	GLuint vaoId = 0;

	// Create a new Vertex Array Object on the GPU and assign it to vaoId
	glGenVertexArrays(1, &vaoId);

	if (!vaoId)
	{
		throw std::runtime_error("Couldn't bind the VAO");
	}

	//Bind the VAO as the current used object - This object is going to be drawn
	glBindVertexArray(vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	//Specify how the coordinate data goes into attribute index 0 and has 3 floats per vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0);

	//Enable attribute index 0 as being used
	glEnableVertexAttribArray(0);

	// Bind the color VBO, assign it to position 1 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		2 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ================================================================================================ //

	// Load a texture

	int textureW{ 0 };
	int textureH{ 0 };

	unsigned char* textureData = stbi_load("image.png", &textureW, &textureH, NULL, 4);

	if (!textureData)
	{
		throw std::exception();
	}

	// Create and bind a texture.
	GLuint textureId = 0;
	glGenTextures(1, &textureId);

	if (!textureId)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	// Upload the image data to the bound texture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureW, textureH, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, textureData);

	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);

	free(textureData);

	// Unbind the texture because we are done operating on it
	glBindTexture(GL_TEXTURE_2D, 0);

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
		glBindVertexArray(vaoId);
		glBindTexture(GL_TEXTURE_2D, textureId);

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