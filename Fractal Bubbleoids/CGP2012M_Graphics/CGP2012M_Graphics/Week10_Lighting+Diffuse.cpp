#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>



//include shape, shader header files
#include "GLerror.h"
#include "SDL_Start.h"
#include "Triangle_T.h"
#include "CircleTexture.h"
#include "Square.h"
#include "Camera.h"
#include "Model.h"
#include "ModelLoaderClass.h"
#include "Bubble.h"
#include "Shot.h"
#include "text.h"
#include "Skybox.h"
#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#ifndef SHADERCLASS_H
#define SHADERCLASS_H

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#ifndef GLEW_H
#define GLEW_H
//#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#ifndef SDL_H
#define SDL_H
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_mixer.h"
#include "SDL_ttf.h"

// - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// NOTE: must do before including GLM headers
// NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//***************
//variables
SDL_Event event;
SDL_Window *win;
bool windowOpen = true;
bool isFullScreen = false;
float bubbleSpeed = 0.003f; //default speed used to intialise the bubbles
int bubbleCount = 7;
float radius;

bool catchImmune;

//screen boundaries for collision tests
float bX_r = 2.9f;
float bX_l = -2.9f;
float bY_t = 1.9f;
float bY_b = -1.9f;
//screen centre
float centreX = 0.0f;
float centreY = 0.0f;
//window aspect/width/height
int w;
int h;
float aspect;
int up;
int left;
int newwidth;
int newheight;

//transform matrices
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
glm::mat4 normalMatrix;



glm::mat4 translate;
glm::mat4 rotate;
glm::mat4 scale;
glm::mat4 backgroundTranslate;
glm::mat4 backgroundScale;
glm::vec3 b_scaleFactor;
glm::mat4 modelRotate;
glm::mat4 modelScale;
glm::mat4 modelTranslate;
float angle = 0;


//text specific
const char* txtString;
int loopCounter = 0; //used for text


//create camera
Camera cam;
//loac camera variables
glm::vec3 camPos;
glm::vec3 camTarget;

bool flag = true;

//light vars
//light one
glm::vec3 lightCol;
glm::vec3 lightPosition;
//light two
glm::vec3 lightColLamp;
glm::vec3 lightPositionLamp;

glm::vec3 viewPosition;
float ambientIntensity;

//object variables
std::vector<Bubble*> bubbles;
std::vector<Model*> boundary;
Model* model;
int lives;

//shot specific
Shot* projectile = nullptr;
bool has_Shot = true; //does the player have the ability to shoot
float shotRadius;
float shotSpeed;

//**************
//function prototypes
void updatePositions(Bubble* c);
void updatePositions(Shot* s);
void handleInput();

int main(int argc, char *argv[]) {
	//start and initialise SDL
	SDL_Start sdl;
	SDL_GLContext context = sdl.Init();
	win = sdl.win;

	SDL_GetWindowSize(win, &w, &h);
	glViewport(0, 0, w, h);
	aspect = (float)w / (float)h;

	//error class
	GLerror glerr;
	int errorLabel;

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	//register debug callback
	if (glDebugMessageCallback)
	{
		std::cout << "Registering OpenGL Debug callback function" << std::endl;
		glDebugMessageCallback(glerr.openglCallbackFunction, &errorLabel);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,	0, NULL, true);
	}

	//*****************************************************
	//OpenGL specific data

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//objects
	//create background square
	Square background;
	//create model
	model = new Model(0.0f,0.0f, "..//..//Assets//Models//blenderCube.obj", "..//..//Assets//Textures//bubble tex.png");
	lives = 3;

	//create skybox
	Skybox skycube;

	//create bubbles
	float randValue, randValue2;
	srand(time(0));
	radius = 0.2f;
	shotRadius = 0.3f;

	for (int i = 0; i < bubbleCount; i++)
	{
		bubbles.push_back(new Bubble(0.0f, 0.0f,bubbleSpeed));
	}

	//create boundaries
	for (int i = 0; i < 4; i++)
	{
		boundary.push_back(new Model(0.0f, 0.0f, "..//..//Assets//Models//blenderCube.obj", "..//..//Assets//Textures//boundary.png"));
	}

	errorLabel = 0;

	//*********************
	//create texture collection
	//create textures - space for 4, but only using 2
	Texture texArray[4];
	//background texture
	texArray[0].load("..//..//Assets//Textures//space.png");
	texArray[0].setBuffers();
	texArray[1].load("..//..//Assets//Textures//flag.png");
	texArray[1].setBuffers();

	errorLabel = 2;

	//OpenGL buffers
	background.setBuffers();
	model->setBuffers();
	skycube.setBuffers();

	//set buffers for the circles
	for (int q = 0; q < bubbleCount; q++)
	{
		bubbles[q]->setBuffers();
	}

	//set buffers for boundaries
	for (int i = 0; i < 4; i++)
	{
		boundary[i]->setBuffers();
	}

	errorLabel = 3;
	//*****************************************
	//set uniform variables
	int transformLocation;
	int modelLocation;
	int viewLocation;
	int projectionLocation;
	int importModelLocation;
	int importViewLocation;
	int importProjectionLocation;
	int backgroundColourLocation;
	int ambientIntensityLocation;
	int modelColourLocation;
	int modelAmbientLocation;
	int lightColLocation;
	int lightColLocationLamp;
	int normalMatrixLocation;
	int lightPositionLocation;
	int lightPositionLocationLamp;
	int viewPositionLocation;

	GLuint currentTime = 0;
	GLuint lastTime = 0;
	GLuint elapsedTime = 0;

	//lighting for the model
	//Light position setting
	lightPosition = glm::vec3(1.0f, 0.0f, 0.5f);
	lightPositionLamp = glm::vec3(0.0f,0.0f,0.0f);
	//light colour setting
	// Candle:  r:1.0 g:0.57 b:0.16
	// 100W bulb: r:1.0 g:0.84 b:0.66
	// direct sunlight: r:1.0 g:1.0 b:0.98
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 0.98f);
	glm::vec3 lampColour = glm::vec3(1.0f, 0.3f, 0.3f);

	//light for the background
	//light distance setting
	ambientIntensity = 1.0f;
	lightCol = glm::vec3(1.0f, 1.0f, 0.98f);
	lightColLamp = glm::vec3(20.0f, 20.0f, 20.0f);

	//initialise transform matrices 

	//perspective (3D) projection
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
	//initialise view matrix to '1'
	viewMatrix = glm::mat4(1.0f);

	backgroundScale = glm::mat4(1.0f);
	backgroundTranslate = glm::mat4(1.0f);
	modelScale = glm::mat4(1.0f);
	modelRotate = glm::mat4(1.0f);
	modelTranslate = glm::mat4(1.0f);

	

	//once only scale to background, and translate to centre
	b_scaleFactor = { 60.0f, 50.0f, 1.0f };
	backgroundScale = glm::scale(backgroundScale, glm::vec3(b_scaleFactor));
	backgroundTranslate = glm::translate(backgroundTranslate, glm::vec3(0.0f, 0.0f, -2.0f));

	//once only scale and translate to model
	modelScale = glm::scale(modelScale, glm::vec3(0.1f, 0.1f, 0.1f));
	modelTranslate = glm::translate(modelTranslate, glm::vec3(0.0f, 0.0f, 0.0f));

	//boundary translations
	boundary[0]->scale = glm::scale(boundary[0]->scale, glm::vec3(3.2f, 0.2f, 1.0f));
	boundary[0]->translate = glm::translate(boundary[0]->translate, glm::vec3(0.0f, 2.0f, 0.5f));

	boundary[1]->scale = glm::scale(boundary[1]->scale, glm::vec3(3.2f, 0.2f, 1.0f));
	boundary[1]->translate = glm::translate(boundary[1]->translate, glm::vec3(0.0f, -2.0f, 0.5f));

	boundary[2]->scale = glm::scale(boundary[2]->scale, glm::vec3(0.2f, 1.8f, 1.0f));
	boundary[2]->translate = glm::translate(boundary[2]->translate, glm::vec3(3.0f, 0.0f, 0.5f));

	boundary[3]->scale = glm::scale(boundary[3]->scale, glm::vec3(0.2f, 1.8f, 1.0f));
	boundary[3]->translate = glm::translate(boundary[3]->translate, glm::vec3(-3.0f, 0.0f, 0.5f));
	

	for (int q = 0; q < bubbleCount; q++)
	{
		randValue = (float)(rand() % ((int)bX_r * 100) + 1) / 100.0f;
		randValue2 = (float)(rand() % ((int)bY_t * 100) + 1) / 100.0f;
		std::cout << "1: " << randValue << " 2: " << randValue2 << std::endl;
		bubbles[q]->sprite->translate = glm::translate(bubbles[q]->sprite->translate, glm::vec3(randValue, randValue2, 0.0f));
		bubbles[q]->sprite->x += randValue;
		bubbles[q]->sprite->y += randValue2;
	}


	errorLabel = 4;

	//on screen text
	std::string temp;
	//set what font is used - .ttf file in 'Fonts' folder
	Text osText("..//..//assets//fonts//cour.ttf");

	//*****************************
	//'game' loop
	while (windowOpen)
	{
		//*************************
		//****************************
		// OpenGL calls.

		//projectile collision checks
		if (!has_Shot)
		{
			if (bubbleCount > 0)
			{
				bool checking = true;
				int i = 0;
				while (checking)
				{
					if (sqrt(pow(bubbles[i]->sprite->x - projectile->sprite->x, 2.0f) + pow(bubbles[i]->sprite->y - projectile->sprite->y, 2.0f)) <= (shotRadius / 2) + (radius * 2))
					{
						delete bubbles[i];
						bubbles.erase(bubbles.begin() + i);
						bubbleCount -= 1;
					}
					else
					{
						i += 1;
					}
					if (i == bubbleCount)
					{
						checking = false;
					}
				}
			}
			//shot radius is modified to be slightly larger so the player doesn't catch it immediately after firing it while moving forwards
			if (catchImmune &&sqrt(pow(model->x - projectile->sprite->x, 2.0f) + pow(model->y - projectile->sprite->y, 2.0f)) >= shotRadius) 
			{
				catchImmune = false;
			}
			if (!catchImmune &&sqrt(pow(model->x - projectile->sprite->x, 2.0f) + pow(model->y - projectile->sprite->y, 2.0f)) <= shotRadius)
			{
				delete projectile;
				has_Shot = true;
			}
		}

		if (lives>=0&& bubbleCount > 0)
		{
			bool checking = true;
			int i = 0;
			while (checking)
			{
				if (sqrt(pow(bubbles[i]->sprite->x - model->x, 2.0f) + pow(bubbles[i]->sprite->y - model->y, 2.0f)) <= (radius * 2))
				{
					lives -= 1;
					bubbles[i]->Xspeed *= -1.0f;
					bubbles[i]->Yspeed *= -1.0f;
					checking = false;
				}
				i += 1;
				if (i == bubbleCount)
				{
					checking = false;
				}
			}
		}
		
		//##########################################################################################################

		glClearColor(1.0f, 1.0f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//process inputs
		handleInput();
		cam.updateCamera();

		//time
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		//update camera matrix
		//camera only moves side to side, formards and backwards (no rotation)
		// set position, target, up direction
		viewMatrix = glm::lookAt(glm::vec3(cam.camXPos, cam.camYPos, cam.camZPos), cam.cameraTarget, cam.cameraUp);

		errorLabel = 5;

		//background
		//glUseProgram(background.shaderProgram);
		//set background lighting
		//backgroundColourLocation = glGetUniformLocation(background.shaderProgram, "uLightColour");
		//glProgramUniform3fv(background.shaderProgram, backgroundColourLocation, 1, glm::value_ptr(lightCol));
		//light distance
		//ambientIntensityLocation = glGetUniformLocation(background.shaderProgram, "uAmbientIntensity");
		//glProgramUniform1f(background.shaderProgram, ambientIntensityLocation, ambientIntensity);

		//set background image
		//modelLocation = glGetUniformLocation(background.shaderProgram, "uModel");
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(backgroundTranslate*backgroundScale));
		//viewLocation = glGetUniformLocation(background.shaderProgram, "uView");
		//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		//projectionLocation = glGetUniformLocation(background.shaderProgram, "uProjection");
		//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		//glBindTexture(GL_TEXTURE_2D, texArray[0].texture);
		//background.render();

		////set skybox
		glDepthMask(GL_FALSE);
		glUseProgram(skycube.shaderProgram);
		skycube.viewLocation = glGetUniformLocation(skycube.shaderProgram, "viewLocation");
		glUniformMatrix4fv(skycube.viewLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));
		//glUniformMatrix4fv(skycube.viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		skycube.projectionLocation = glGetUniformLocation(skycube.shaderProgram, "projectionLocation");
		glUniformMatrix4fv(skycube.projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		
		skycube.render();
		glDepthMask(GL_TRUE);

		lightPositionLamp = glm::vec3(model->x, model->y, 0.0f);

		////set .obj model
		glUseProgram(model->shaderProgram);
		//lighting uniforms
		//get and set light colour and position uniform
		lightColLocation = glGetUniformLocation(model->shaderProgram, "lightCol");
		glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
		lightPositionLocation = glGetUniformLocation(model->shaderProgram, "lightPos");
		glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));

		lightColLocationLamp = glGetUniformLocation(model->shaderProgram, "lightColLamp");
		glUniform3fv(lightColLocationLamp, 1, glm::value_ptr(lampColour));
		lightPositionLocationLamp = glGetUniformLocation(model->shaderProgram, "lightPosLamp");
		glUniform3fv(lightPositionLocationLamp, 1, glm::value_ptr(lightPositionLamp));

		//rotation
		modelRotate = glm::rotate(modelRotate, (float)elapsedTime / 2000, glm::vec3(-1.0f, 0.0f, 0.0f)); //magnitude of vec 3 irrelevant, only polatrity matters, magnitude controlled by elapsedTime equation
		modelRotate = glm::rotate(modelRotate, (float)elapsedTime / 2000, glm::vec3(0.0f, 1.0f, 0.0f));
		modelRotate = glm::rotate(modelRotate, (float)elapsedTime / 2000, glm::vec3(0.0f, 0.0f, -1.0f));
		importModelLocation = glGetUniformLocation(model->shaderProgram, "uModel");
		glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(modelTranslate*modelRotate*modelScale));
		importViewLocation = glGetUniformLocation(model->shaderProgram, "uView");
		glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		importProjectionLocation = glGetUniformLocation(model->shaderProgram, "uProjection");
		glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		//set the normal matrix to send to the vertex shader
		//Light calculations take place in model-view space
		//So we calculate the normal matrix in that space
		normalMatrix = glm::transpose(glm::inverse(modelTranslate*modelRotate*modelScale * viewMatrix));
		//set the normalMatrix in the shaders
		glUseProgram(model->shaderProgram);
		normalMatrixLocation = glGetUniformLocation(model->shaderProgram, "uNormalMatrix");
		glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glBindTexture(GL_TEXTURE_2D, texArray[1].texture);
		model->render();

		//render the boundaries
		for (int q = 0; q < 4; q++)
		{
			//std::cout << "###boundary start###" << std::endl;
			glUseProgram(boundary[q]->shaderProgram);
			//std::cout << "lighting" << std::endl;
			//lighting uniforms
			//get and set light colour and position uniform
			lightColLocation = glGetUniformLocation(boundary[q]->shaderProgram, "lightCol");
			glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
			lightPositionLocation = glGetUniformLocation(boundary[q]->shaderProgram, "lightPos");
			glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));

			lightColLocationLamp = glGetUniformLocation(boundary[q]->shaderProgram, "lightColLamp");
			glUniform3fv(lightColLocationLamp, 1, glm::value_ptr(lampColour));
			lightPositionLocationLamp = glGetUniformLocation(boundary[q]->shaderProgram, "lightPosLamp");
			glUniform3fv(lightPositionLocationLamp, 1, glm::value_ptr(lightPositionLamp));

			//std::cout << "projection matrix" << std::endl;
			//set projection matrix uniform
			boundary[q]->modelLocation = glGetUniformLocation(boundary[q]->shaderProgram, "uModel");
			glUniformMatrix4fv(boundary[q]->modelLocation, 1, GL_FALSE, glm::value_ptr(boundary[q]->translate*boundary[q]->scale));
			boundary[q]->viewLocation = glGetUniformLocation(boundary[q]->shaderProgram, "uView");
			glUniformMatrix4fv(boundary[q]->viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			boundary[q]->projectionLocation = glGetUniformLocation(boundary[q]->shaderProgram, "uProjection");
			glUniformMatrix4fv(boundary[q]->projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			//std::cout << "normal matrix" << std::endl;
			//set the normal matrix to send to the vertex shader
			//Light calculations take place in model-view space
			//So we calculate the normal matrix in that space
			normalMatrix = glm::transpose(glm::inverse(boundary[q]->translate*boundary[q]->rotate*boundary[q]->scale * viewMatrix));
			//set the normalMatrix in the shaders
			glUseProgram(boundary[q]->shaderProgram);
			normalMatrixLocation = glGetUniformLocation(boundary[q]->shaderProgram, "uNormalMatrix");
			glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
			//glBindVertexArray(bubbles[q]->sprite->VAO);
			glBindTexture(GL_TEXTURE_2D, boundary[q]->skin.texture);
			//std::cout << "render" << std::endl;
			boundary[q]->render();
			//std::cout << "###boundary end###" << std::endl;
		}

		//render the bubbles
		for (int q = 0; q < bubbleCount; q++)
		{
			updatePositions(bubbles[q]);

			glUseProgram(bubbles[q]->sprite->shaderProgram);
			
			//lighting uniforms
			//get and set light colour and position uniform
			lightColLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "lightCol");
			glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
			lightPositionLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "lightPos");
			glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));

			lightColLocationLamp = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "lightColLamp");
			glUniform3fv(lightColLocationLamp, 1, glm::value_ptr(lampColour));
			lightPositionLocationLamp = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "lightPosLamp");
			glUniform3fv(lightPositionLocationLamp, 1, glm::value_ptr(lightPositionLamp));
			
			//set projection matrix uniform
			bubbles[q]->sprite->modelLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uModel");
			glUniformMatrix4fv(bubbles[q]->sprite->modelLocation, 1, GL_FALSE, glm::value_ptr(bubbles[q]->sprite->translate*bubbles[q]->sprite->scale));
			bubbles[q]->sprite->viewLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uView");
			glUniformMatrix4fv(bubbles[q]->sprite->viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			bubbles[q]->sprite->projectionLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uProjection");
			glUniformMatrix4fv(bubbles[q]->sprite->projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

			//set the normal matrix to send to the vertex shader
			//Light calculations take place in model-view space
			//So we calculate the normal matrix in that space
			normalMatrix = glm::transpose(glm::inverse(bubbles[q]->sprite->translate*bubbles[q]->sprite->rotate*bubbles[q]->sprite->scale * viewMatrix));
			//set the normalMatrix in the shaders
			glUseProgram(bubbles[q]->sprite->shaderProgram);
			normalMatrixLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uNormalMatrix");
			glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
			//glBindVertexArray(bubbles[q]->sprite->VAO);
			glBindTexture(GL_TEXTURE_2D, bubbles[q]->sprite->skin.texture);
			bubbles[q]->sprite->render();
		}

		if (!has_Shot&&projectile != nullptr)
		{

			updatePositions(projectile);
			
			glUseProgram(projectile->sprite->shaderProgram);

			//lighting uniforms
			//get and set light colour and position uniform
			lightColLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "lightCol");
			glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
			lightPositionLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "lightPos");
			glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));

			lightColLocationLamp = glGetUniformLocation(projectile->sprite->shaderProgram, "lightColLamp");
			glUniform3fv(lightColLocationLamp, 1, glm::value_ptr(lampColour));
			lightPositionLocationLamp = glGetUniformLocation(projectile->sprite->shaderProgram, "lightPosLamp");
			glUniform3fv(lightPositionLocationLamp, 1, glm::value_ptr(lightPositionLamp));

			//set projection matrix uniform
			projectile->sprite->modelLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uModel");
			glUniformMatrix4fv(projectile->sprite->modelLocation, 1, GL_FALSE, glm::value_ptr(projectile->sprite->translate*projectile->sprite->scale));
			projectile->sprite->viewLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uView");
			glUniformMatrix4fv(projectile->sprite->viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			projectile->sprite->projectionLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uProjection");
			glUniformMatrix4fv(projectile->sprite->projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

			//set the normal matrix to send to the vertex shader
			//Light calculations take place in model-view space
			//So we calculate the normal matrix in that space
			normalMatrix = glm::transpose(glm::inverse(projectile->sprite->translate*projectile->sprite->rotate*projectile->sprite->scale * viewMatrix));
			//set the normalMatrix in the shaders
			glUseProgram(projectile->sprite->shaderProgram);
			normalMatrixLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uNormalMatrix");
			glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
			glBindVertexArray(projectile->sprite->VAO);
			glBindTexture(GL_TEXTURE_2D, projectile->sprite->skin.texture);
			projectile->sprite->render();
		}

		//render the text
		temp = std::to_string(lives);
		//set text to display 'temp' and set it to a white colour
		//SDL uses 0-255 for colours rather that 0-1 in OpenGL
		//The text that is rendered could be anything - changed when an event happens for example.
		osText.setText(temp.c_str(), 255, 0, 0);
		osText.render();

		SDL_GL_SwapWindow(sdl.win);

		loopCounter++;
		if (lives < 0)
		{
			windowOpen = false;
		}
	}//end loop

	//****************************
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;
}

void updatePositions(Bubble* c) 
{
	//update positions of the bubbles
	if (c->sprite->x > (bX_r - (radius * 2)) && (c->Xspeed > 0))
	{
		c->Xspeed *= -1.0f;		
	}
	else if (c->sprite->x < (bX_l + (radius * 2))&&(c->Xspeed < 0))
	{
		c->Xspeed *= -1.0f;
	}
	if (c->sprite->y > (bY_t - (radius * 2)) && (c->Yspeed > 0))
	{
		c->Yspeed *= -1.0f;
	}
	else if (c->sprite->y < (bY_b + (radius * 2)) && (c->Yspeed < 0))
	{
		c->Yspeed *= -1.0f;
	}
	c->sprite->translate = glm::translate(c->sprite->translate, glm::vec3(c->Xspeed, c->Yspeed, 0.0f));
	c->sprite->x += c->Xspeed;
	c->sprite->y += c->Yspeed;
}
void updatePositions(Shot* s)
{
	//update positions of the bubbles
	if (s->sprite->x > (bX_r - (radius/2)) && (s->Xspeed > 0))
	{
		s->Xspeed *= -1.0f;
	}
	else if (s->sprite->x < (bX_l + (radius/2)) && (s->Xspeed < 0))
	{
		s->Xspeed *= -1.0f;
	}
	if (s->sprite->y > (bY_t - (radius/2)) && (s->Yspeed > 0))
	{
		s->Yspeed *= -1.0f;
	}
	else if (s->sprite->y < (bY_b + (radius/2)) && (s->Yspeed < 0))
	{
		s->Yspeed *= -1.0f;
	}
	s->sprite->translate = glm::translate(s->sprite->translate, glm::vec3(s->Xspeed, s->Yspeed, 0.0f));
	s->sprite->x += s->Xspeed;
	s->sprite->y += s->Yspeed;
}

void handleInput()
{
	//*****************************
		//SDL handled input
		//Any input to the program is done here

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			windowOpen = false;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				std::cout << "Window resized w:" << w << " h:" << h << std::endl;
				SDL_GetWindowSize(win, &w, &h);
				if ((aspect*h) < w)
				{
					newwidth = h * aspect;
					left = (w - newwidth) / 2;
					glViewport(left, 0, newwidth, h);
				}
				else
				{
					newheight = w * (1 / aspect);
					up = (h - newheight) / 2;
					glViewport(0, up, w, newheight);
				}
				//SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				break;


			default:
				break;
			}
		}

		if (event.type == SDL_KEYDOWN)
		{
			float tempX; //used to store random x co-ord when teleporting
			float tempY; //used to store random y co-ord when teleporting
			std::cout << "Key Down " << event.key.keysym.sym << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_RSHIFT:
				//std::cout << "Right Shift" << std::endl;
				if (has_Shot)
				{
					projectile = new Shot(0.0f, 0.0f, angle);
					catchImmune = true;
					projectile->setBuffers();
					projectile->sprite->translate = glm::translate(modelTranslate, glm::vec3(0.0f, 0.0f, 0.0f)); //apparently this line is crucial no idea why
					projectile->sprite->x = model->x;
					projectile->sprite->y = model->y;
					has_Shot = false;
				}
				break;

			case SDLK_SPACE:
				//std::cout << "Space" << std::endl;
				tempX = (float)(rand() % ((int)bX_r * 100) + 1) / 100.0f;
				tempY = (float)(rand() % ((int)bY_t * 100) + 1) / 100.0f;
				modelTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(tempX, tempY, 0.0f));
				model->x += tempX;
				model->y += tempY;
				break;
			case SDLK_UP:
				//std::cout << "Up" << std::endl;
				modelTranslate = glm::translate(modelTranslate, glm::vec3((float)cos(angle)*0.08f, (float)sin(angle)*0.08f, 0.0f));
				model->x += (float)cos(angle)*0.08f;
				model->y += (float)sin(angle)*0.08f;
				break;
			case SDLK_DOWN:
				//std::cout << "Down" << std::endl;
				modelTranslate = glm::translate(modelTranslate, -glm::vec3((float)sin(glm::radians(90.0f) - angle)*0.04f, (float)cos(glm::radians(90.0f) - angle)*0.04f, 0.0f));
				model->x += -((float)sin(glm::radians(90.0f) - angle)*0.04f);
				model->y += -((float)cos(glm::radians(90.0f) - angle)*0.04f);
				break;
			case SDLK_LEFT:
				//std::cout << "Left" << std::endl;
				angle += glm::radians(10.0f);
				modelRotate = glm::rotate(modelRotate, glm::radians(10.0f), glm::vec3(0, 0, 1));
				break;
			case SDLK_RIGHT:
				//std::cout << "Right" << std::endl;
				angle -= glm::radians(10.0f);
				modelRotate = glm::rotate(modelRotate, glm::radians(-10.0f), glm::vec3(0, 0, 1));
				break;
			case SDLK_f:
				//std::cout << "F" << std::endl;
				if (isFullScreen)
				{
					SDL_SetWindowFullscreen(win, 0);
					isFullScreen = false;
				}
				else if (!isFullScreen)
				{
					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
					isFullScreen = true;
				}
				break;

			case SDLK_EQUALS:
				//std::cout << "P" << std::endl;
				//move camera 'forward' in the -ve z direction
				cam.camZPos -= cam.camSpeed;
				break;
			case SDLK_MINUS:
				//std::cout << "l" << std::endl;
				//move camera 'backwards' in +ve z direction
				cam.camZPos += cam.camSpeed;
				break;
			case SDLK_a:
				//std::cout << "z" << std::endl;
				//move camera left
				//move camera target with position
				cam.camXPos -= cam.camSpeed;
				cam.camXTarget -= cam.camSpeed;
				break;
			case SDLK_d:
				//std::cout << "x" << std::endl;
				//move camera right
				//move camera target with position
				cam.camXPos += cam.camSpeed;
				cam.camXTarget += cam.camSpeed;
				break;

			case SDLK_w:
				//std::cout << "o" << std::endl;
				//move camera up
				cam.camYPos += cam.camSpeed;
				cam.camYTarget += cam.camSpeed;
				break;
			case SDLK_s:
				//std::cout << "k" << std::endl;
				//move camera down
				cam.camYPos -= cam.camSpeed;
				cam.camYTarget -= cam.camSpeed;
				break;
			case SDLK_q:
				//std::cout << "k" << std::endl;
				//aim camera up
				cam.camYTarget += cam.camSpeed;
				break;
			case SDLK_e:
				//std::cout << "k" << std::endl;
				//move cameera down
				cam.camYTarget -= cam.camSpeed;
				break;
			/*
			case SDLK_v:
				//std::cout << "v" << std::endl;
				lightPosition.x -= 0.1f;
				break;
			case SDLK_b:
				//std::cout << "b" << std::endl;
				lightPosition.x += 0.1f;
				break;
			*/

			}
		}
		
	}
}
#endif
#endif
#endif
#endif