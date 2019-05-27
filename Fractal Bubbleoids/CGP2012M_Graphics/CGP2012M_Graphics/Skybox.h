#pragma once
#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "ModelLoaderClass.h"
#include "TextureClass.h"

#include "SDL.h"
#include "SDL_image.h"

class Skybox
{
public:
	


	SDL_Surface* Right;
	SDL_Surface* Left;
	SDL_Surface* Top;
	SDL_Surface* Bottom;
	SDL_Surface* Back;
	SDL_Surface* Front;
	unsigned int Cube;

	//uniforms
	int viewLocation;
	int projectionLocation;
	


	//transforms
	glm::mat4 translate;
	glm::mat4 rotate;
	glm::mat4 scale;


	//vertex/texture coord/normal containers for the model
	//std::vector<GLuint> indices;
	//std::vector<glm::vec2> texCoords;
	//std::vector<glm::vec3> normals;

	//interleaved vertex, texture, normal data
	//more efficient than separate VBO's
	//std::vector<GLfloat> modelData;

	//set up vertex buffer object
	GLuint VBO;
	//set up vertex array object
	GLuint VAO;
	//set up index buffer object
	//GLuint EBO;
	//shader for the model
	Shader vSh, fSh;
	GLuint shaderProgram;

	//define vertices for the Cube
	GLfloat vertices[288] = {
		//vertices			 colour values    texture coords      normals
	 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f,    //0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 0.0f,    //0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 1.0f,    //0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 1.0f,    //0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,   1.0f,0.0f,  0.0f,	0.0f, 1.0f,    //0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	0.0f, 0.0f,    //0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    //0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,    //0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    //0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 0.0f,		1.0f, 1.0f,    //0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,    //0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    //0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    //-1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,    //-1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    //-1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    //-1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,    //-1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    //-1.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     //1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,0.0f, 0.0f,		0.0f, 1.0f,     //1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     //0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,     //0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //0.0f, -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     //0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     //0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,     //0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     //0.0f, 1.0f, 0.0f
	};

	//constructor
	Skybox()
	{

		scale = glm::mat4(1.0f);
		rotate = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);

		

		Right = IMG_Load("..//..//Assets//Textures//Skybox//right.png");
		if (Right == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//right.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//right.png" << std::endl;
		}

		Left = IMG_Load("..//..//Assets//Textures//Skybox//left.png");
		if (Left == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//left.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//left.png" << std::endl;
		}

		Top = IMG_Load("..//..//Assets//Textures//Skybox//top.png");
		if (Top == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//top.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//top.png" << std::endl;
		}

		Bottom = IMG_Load("..//..//Assets//Textures//Skybox//bottom.png");
		if (Bottom == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//bottom.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//bottom.png" << std::endl;
		}

		Back = IMG_Load("..//..//Assets//Textures//Skybox//back.png");
		if (Back == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//back.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//back.png" << std::endl;
		}

		Front = IMG_Load("..//..//Assets//Textures//Skybox//front.png");
		if (Front == NULL)
		{
			std::cout << "Error loading texture: " << "..//..//Assets//Textures//Skybox//front.png" << std::endl;
		}
		else
		{
			std::cout << "Success loading " << "..//..//Assets//Textures//Skybox//front.png" << std::endl;
		}
		

		//shaders
		vSh.shaderFileName("..//..//Assets//Shaders//shader_skybox.vert");
		fSh.shaderFileName("..//..//Assets//Shaders//shader_skybox.frag");

		vSh.getShader(1);
		fSh.getShader(2);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vSh.shaderID);
		glAttachShader(shaderProgram, fSh.shaderID);
		glLinkProgram(shaderProgram);

		glDeleteShader(vSh.shaderID);
		glDeleteShader(fSh.shaderID);
	};



	void setBuffers()
	{
		std::cout << "###Skybox Buffers Start###" << std::endl;
		glGenTextures(1, &Cube);
		glBindTexture(GL_TEXTURE_CUBE_MAP, Cube);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, Right->w, Right->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Right->pixels);		
		SDL_FreeSurface(Right);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, Left->w, Left->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Left->pixels);
		SDL_FreeSurface(Left);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, Top->w, Top->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Top->pixels);		
		SDL_FreeSurface(Top);
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, Bottom->w, Bottom->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Bottom->pixels);
		SDL_FreeSurface(Bottom);
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, Back->w, Back->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Back->pixels);		
		SDL_FreeSurface(Back);
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, Front->w, Front->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Front->pixels);
		SDL_FreeSurface(Front);
		

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		//
		//OpenGL buffers
		//set up 1 for the cube
		glGenBuffers(1, &VBO);
		// Initialization code using Vertex Array Object (VAO) (done once (unless the object frequently changes))
		glGenVertexArrays(1, &VAO);
		//initialise the index buffer
		//glGenBuffers(1, &this->EBO);
		// Bind Vertex Array Object
		glBindVertexArray(VAO);
		// Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//set the colour attribute pointer
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//set texture attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		//set normal attrib pointer
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(3);

		//Unbind the VAO
		glBindVertexArray(0);

		std::cout << "###Skybox Buffers End###" << std::endl;
	}

	void render()
	{
		//draw the square 
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(vertices));
		glBindTexture(GL_TEXTURE_CUBE_MAP, Cube);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

};