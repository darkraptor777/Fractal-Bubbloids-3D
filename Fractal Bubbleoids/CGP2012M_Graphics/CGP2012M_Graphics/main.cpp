//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#include <vector>
//#include <cmath>
////TODO//
//
////Player collect projectile
////you win/lose screen
////game ends when lives <0
//
////include shape, shader header files
//#include "GLerror.h"
//#include "SDL_Start.h"
//#include "Camera.h"
//#include "Model.h"
//#include "ModelLoaderClass.h"
//#include "Triangle_T.h"
//#include "CircleTexture.h"
//#include "Square.h"
//#include "Bubble.h"
//#include "Shot.h"
//#include "text.h"
//#ifndef TEXTURECLASS_H
//#define TEXTURECLASS_H
//#ifndef SHADERCLASS_H
//#define SHADERCLASS_H
//
//
//// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
//// // NOTE: include before SDL.h
//#ifndef GLEW_H
//#define GLEW_H
////#include <GL/glew.h>
//#include "windows.h"
//
//// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
//#ifndef SDL_H
//#define SDL_H
//#include "SDL.h"
//#include "SDL_image.h"
////#include "SDL_mixer.h"
////#include "SDL_ttf.h"
//
//// // - OpenGL Mathematics - https://glm.g-truc.net/
//#define GLM_FORCE_RADIANS // force glm to use radians
//// // NOTE: must do before including GLM headers
//// // NOTE: GLSL uses radians, so will do the same, for consistency
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
////***************
////variables
//SDL_Event event;
//SDL_Window *win;
//bool windowOpen = true;
//bool isFullScreen = false;
//float bubbleSpeed = 0.003f; //default speed used to intialise the bubbles
//int bubbleCount = 7;
//float radius;
//float shotRadius;
//float shotSpeed;
//
//bool catchImmune;
//
////screen boundaries for collision tests
//const float bX_r = 4.0f;
//const float bX_l = 0.0f;
//const float bY_t = 3.0f;
//const float bY_b = 0.0f;
////screen centre
//float centreX = bX_r/2.0f;
//float centreY = bY_t / 2.0f;
////window aspect/width/height
//int w;
//int h;
//float aspect;
//int left;
//int up;
//int newwidth;
//int newheight;
////text specific
//const char* txtString;
//int loopCounter = 0; //used for text
//
////shot specific
//Shot* projectile;
//bool has_Shot = true; //does the player have the ability to shoot
//
////transform matrices
//glm::mat4 modelMatrix;
//glm::mat4 viewMatrix;
//glm::mat4 projectionMatrix;
//
//glm::mat4 translate;
//
//glm::mat4 shotScale;
//glm::mat4 bubbleScale;
//glm::mat4 rotate;
//glm::mat4 scale;
//glm::mat4 backgroundTranslate;
//glm::mat4 backgroundScale;
//glm::mat4 boundaryTranslate;
//glm::mat4 boundaryScale;
//glm::vec3 b_scaleFactor;
//float angle = 0;
//
//
////create camera
//Camera cam;
////loac camera variables
//glm::vec3 camPos;
//glm::vec3 camTarget;
//
//
//
//
//std::vector<Bubble*> bubbles;
//
////create triangle
//Model* player = nullptr;
//int lives;
//
//glm::vec3 lightCol;
//float ambientIntensity;
//
////**************
////function prototypes
//void updatePositions(Bubble* c);
//void updatePositions(Shot* s);
//void handleInput();
//
//int main(int argc, char *argv[]) {
//	//start and initialise SDL
//	SDL_Start sdl;
//	SDL_GLContext context = sdl.Init();
//	SDL_DisplayMode DM;
//	SDL_GetCurrentDisplayMode(0, &DM);
//	w = DM.w/2;
//	h= DM.h/2;
//	win = sdl.win;
//	SDL_SetWindowSize(win, w, h);
//	SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
//	//SDL_CreateWindow("Luke Howard #15623020 Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
//
//	//SDL_GetWindowSize(win, &w, &h);
//	glViewport(0, 0, w, h);
//	aspect = (float)w / (float)h;
//
//	//error class
//	GLerror glerr;
//	int errorLabel;
//
//	//GLEW initialise
//	glewExperimental = GL_TRUE;
//	GLenum err = glewInit();
//
//	//register debug callback
//	if (glDebugMessageCallback)
//	{
//		std::cout << "Registering OpenGL Debug callback function" << std::endl;
//		glDebugMessageCallback(glerr.openglCallbackFunction, &errorLabel);
//		glDebugMessageControl(GL_DONT_CARE,
//			GL_DONT_CARE,
//			GL_DONT_CARE,
//			0,
//			NULL,
//			true);
//	}
//
//	//*****************************************************
//	//OpenGL specific data
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	//create player
//	player = new Model(centreX, centreY);
//	lives = 3;
//
//	//create background and boundary
//	Square background;
//	Square boundary;
//
//	//create bubbles
//	float randValue, randValue2;
//	srand(time(0));
//	radius = 0.2f;
//	shotRadius = 0.2f;
//
//	for (int i = 0; i < bubbleCount; i++)
//	{
//		bubbles.push_back(new Bubble(radius, 0.0f, 0.0f,bubbleSpeed));
//		//bubbles.push_back(new Bubble(radius, 0.0f, 0.0f));
//	}
//
//	errorLabel = 0;
//
//	//*********************
//	//create texture collection
//	//create textures - space for 4, but only using 1
//	Texture texArray[5];
//	//background texture
//	texArray[0].load("..//..//Assets//Textures//background.png");
//	texArray[0].setBuffers();
//	//wall textures
//	texArray[1].load("..//..//Assets//Textures//boundary.png");
//	texArray[1].setBuffers();
//	
//
//	errorLabel = 2;
//
//	//OpenGL buffers
//	player->setBuffers();
//	background.setBuffers();
//	boundary.setBuffers();
//	
//	//set buffers for the circles
//	for (int q = 0; q < bubbleCount; q++)
//	{
//		bubbles[q]->sprite->setBuffers();
//	}
//
//	errorLabel = 3;
//	//*****************************************
//	//set uniform variables
//	int transformLocation;
//	int modelLocation;
//	int viewLocation;
//	int projectionLocation;
//	int circleTransformLocation;
//	int backgroundColourLocation;
//	int boundaryColourLocation;
//	int ambientIntensityLocation;
//
//	//light colour initial setting
//	lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
//	//light distance setting
//	ambientIntensity = 1.0f;
//
//	//initialise transform matrices 
//	//orthographic (2D) projection
//	projectionMatrix = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, -1.0f, 100.0f);
//	//initialise view matrix to '1'
//	viewMatrix = glm::mat4(1.0f);
//
//	
//	bubbleScale = glm::mat4(1.0f);
//	shotScale = glm::mat4(1.0f);
//	translate = glm::mat4(1.0f);
//	rotate = glm::mat4(1.0f);
//	scale = glm::mat4(1.0f);
//	backgroundScale = glm::mat4(1.0f);
//	backgroundTranslate = glm::mat4(1.0f);
//	boundaryScale = glm::mat4(1.0f);
//	boundaryTranslate = glm::mat4(1.0f);
//
//	//once only scale to background
//	b_scaleFactor = { 20.0f, 15.0f, 1.0f };
//	backgroundScale = glm::scale(backgroundScale, glm::vec3(b_scaleFactor));
//	backgroundTranslate = glm::translate(backgroundTranslate, glm::vec3(2.0f, 1.5f, 0.0f));
//	boundaryScale = glm::scale(boundaryScale, glm::vec3(b_scaleFactor));
//	boundaryTranslate = glm::translate(boundaryTranslate, glm::vec3(2.0f, 1.5f, 0.0f));
//
//	//once only scale to triangle
//	scale = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.0f));
//
//	bubbleScale = glm::scale(bubbleScale, glm::vec3(2.0f, 2.0f, 0.0f));
//	shotScale = glm::scale(shotScale, glm::vec3(0.5f, 0.5f, 0.0f));
//
//	//once only translate - translate triangle into centre of screen
//	glUseProgram(player->shaderProgram);
//	translate = glm::translate(translate, glm::vec3(2.0f, 1.5f, 0.0f));
//	modelLocation = glGetUniformLocation(player->shaderProgram, "uModel");
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(translate*rotate*scale));
//	//once only translate - translate circle into centre of screen
//	for (int q = 0; q < bubbleCount; q++)
//	{
//		randValue = (float)(rand() % ((int)bX_r * 100) + 1) / 100.0f;
//		randValue2 = (float)(rand() % ((int)bY_t * 100) + 1) / 100.0f;
//		std::cout << "1: " << randValue << " 2: " << randValue2 << std::endl;
//		bubbles[q]->sprite->translate = glm::translate(bubbles[q]->sprite->translate, glm::vec3(randValue, randValue2, 0.0f));
//		bubbles[q]->sprite->x += randValue;
//		bubbles[q]->sprite->y += randValue2;
//	}
//	
//
//	errorLabel = 4;
//
//	//on screen text
//	std::string temp;
//	//set what font is used - .ttf file in 'Fonts' folder
//	Text osText("..//..//assets//fonts//cour.ttf");
//
//	
//
//	//*****************************
//	//'game' loop
//	while (windowOpen)
//	{
//		//*************************
//		
//		//process inputs
//		
//		handleInput();
//
//		//*************************
//
//		//projectile collision checks
//		if (!has_Shot)
//		{
//			if (bubbleCount > 0)
//			{
//				bool checking = true;
//				int i = 0;
//				while (checking)
//				{
//					if (sqrt(pow(bubbles[i]->sprite->x - projectile->sprite->x, 2.0f) + pow(bubbles[i]->sprite->y - projectile->sprite->y, 2.0f)) <= (shotRadius / 2) + (radius * 2))
//					{
//						delete bubbles[i];
//						bubbles.erase(bubbles.begin() + i);
//						bubbleCount -= 1;
//					}
//					else
//					{
//						i += 1;
//					}
//					if (i == bubbleCount)
//					{
//						checking = false;
//					}
//				}
//			}
//
//			if (catchImmune &&sqrt(pow(player->x - projectile->sprite->x, 2.0f) + pow(player->y - projectile->sprite->y, 2.0f)) >= shotRadius) //shot radius is modified to be slightly larger so the player doesn't catch it immediately after firing it while moving forwards
//			{
//				catchImmune = false;
//			}
//			if (!catchImmune &&sqrt(pow(player->x - projectile->sprite->x, 2.0f) + pow(player->y - projectile->sprite->y, 2.0f)) <= shotRadius)
//			{
//				delete projectile;
//				has_Shot = true;
//			}
//		}
//
//		if (lives>=0&& bubbleCount > 0)
//		{
//			bool checking = true;
//			int i = 0;
//			while (checking)
//			{
//				if (sqrt(pow(bubbles[i]->sprite->x - player->x, 2.0f) + pow(bubbles[i]->sprite->y - player->y, 2.0f)) <= (radius * 2))
//				{
//					lives -= 1;
//					bubbles[i]->Xspeed *= -1.0f;
//					bubbles[i]->Yspeed *= -1.0f;
//					checking = false;
//				}
//				i += 1;
//				if (i == bubbleCount)
//				{
//					checking = false;
//				}
//			}
//		}
//
//		//****************************
//		// OpenGL calls.
//		
//		glClearColor(0.0f, 0.0f, 0.0f, 1);
//		glClear(GL_COLOR_BUFFER_BIT); 
//
//		errorLabel = 5;
//		//background
//		glUseProgram(background.shaderProgram);
//
//		//set background lighting
//		backgroundColourLocation = glGetUniformLocation(background.shaderProgram, "uLightColour");
//		glProgramUniform3fv(background.shaderProgram, backgroundColourLocation, 1, glm::value_ptr(lightCol));
//		//light distance
//		ambientIntensityLocation = glGetUniformLocation(background.shaderProgram, "uAmbientIntensity");
//		glProgramUniform1f(background.shaderProgram, ambientIntensityLocation, ambientIntensity);
//
//		//set background image
//		modelLocation = glGetUniformLocation(background.shaderProgram, "uModel");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(backgroundTranslate*backgroundScale));
//		viewLocation = glGetUniformLocation(background.shaderProgram, "uView");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//		projectionLocation = glGetUniformLocation(background.shaderProgram, "uProjection");
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//		glBindTexture(GL_TEXTURE_2D, texArray[0].texture);
//		background.render();
//
//		//boundary
//		glUseProgram(boundary.shaderProgram);
//
//		//set boundary lighting
//		boundaryColourLocation = glGetUniformLocation(boundary.shaderProgram, "uLightColour");
//		glProgramUniform3fv(boundary.shaderProgram, boundaryColourLocation, 1, glm::value_ptr(lightCol));
//		//light distance
//		ambientIntensityLocation = glGetUniformLocation(boundary.shaderProgram, "uAmbientIntensity");
//		glProgramUniform1f(boundary.shaderProgram, ambientIntensityLocation, ambientIntensity);
//
//		//set boundary image
//		modelLocation = glGetUniformLocation(boundary.shaderProgram, "uModel");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(boundaryTranslate*boundaryScale));
//		viewLocation = glGetUniformLocation(boundary.shaderProgram, "uView");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//		projectionLocation = glGetUniformLocation(boundary.shaderProgram, "uProjection");
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//		glBindTexture(GL_TEXTURE_2D, texArray[1].texture);
//		boundary.render();
//
//		//specify shader program to use
//		//to allow transform uniform to be passed in
//		glUseProgram(player->shaderProgram);
//
//		//set projection matrix uniform and other triangle values
//		projectionLocation = glGetUniformLocation(player->shaderProgram, "uProjection");
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//		modelLocation = glGetUniformLocation(player->shaderProgram, "uModel");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(translate*rotate*scale));
//		viewLocation = glGetUniformLocation(player->shaderProgram, "uView");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//		
//		//draw the triangle with a shader and texture
//		player->render();
//
//		//set to wireframe so we can see the circles
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//		//render the bubbles
//		for (int q = 0; q < bubbleCount; q++)
//		{
//			updatePositions(bubbles[q]);
//
//			glUseProgram(bubbles[q]->sprite->shaderProgram);
//			//set projection matrix uniform
//			projectionLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uProjection");
//			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//			modelLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uModel");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(bubbles[q]->sprite->translate*bubbleScale));
//			viewLocation = glGetUniformLocation(bubbles[q]->sprite->shaderProgram, "uView");
//			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//			glBindVertexArray(bubbles[q]->sprite->VAO);
//			bubbles[q]->sprite->render();
//		}
//
//		if(!has_Shot&&projectile!=nullptr)
//		{
//			updatePositions(projectile);
//
//			glUseProgram(projectile->sprite->shaderProgram);
//			//set projection matrix uniform
//			projectionLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uProjection");
//			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//			modelLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uModel");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(projectile->sprite->translate*shotScale));
//			viewLocation = glGetUniformLocation(projectile->sprite->shaderProgram, "uView");
//			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//			glBindVertexArray(projectile->sprite->VAO);
//			projectile->sprite->render();
//		}
//
//		//render the text
//		temp = std::to_string(lives);
//		//set text to display 'temp' and set it to a white colour
//		//SDL uses 0-255 for colours rather that 0-1 in OpenGL
//		//The text that is rendered could be anything - changed when an event happens for example.
//		osText.setText(temp.c_str(), 255, 0, 0);
//		osText.render();
//
//		SDL_GL_SwapWindow(sdl.win);
//
//		loopCounter++;
//
//		if (lives < 0)
//		{
//			windowOpen = false;
//		}
//	}//end loop
//
//	//****************************
//	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
//	SDL_GL_DeleteContext(context);
//
//	SDL_Quit();
//	return 0;
//}
//
//void updatePositions(Bubble* c) 
//{
//	//update positions of the bubbles
//	if (c->sprite->x > (bX_r - (radius * 2)) && (c->Xspeed > 0))
//	{
//		c->Xspeed *= -1.0f;		
//	}
//	else if (c->sprite->x < (bX_l + (radius * 2))&&(c->Xspeed < 0))
//	{
//		c->Xspeed *= -1.0f;
//	}
//	if (c->sprite->y > (bY_t - (radius * 2)) && (c->Yspeed > 0))
//	{
//		c->Yspeed *= -1.0f;
//	}
//	else if (c->sprite->y < (bY_b + (radius * 2)) && (c->Yspeed < 0))
//	{
//		c->Yspeed *= -1.0f;
//	}
//	c->sprite->translate = glm::translate(c->sprite->translate, glm::vec3(c->Xspeed, c->Yspeed, 0.0f));
//	c->sprite->x += c->Xspeed;
//	c->sprite->y += c->Yspeed;
//}
//void updatePositions(Shot* s)
//{
//	//update positions of the bubbles
//	if (s->sprite->x > (bX_r - (radius/2)) && (s->Xspeed > 0))
//	{
//		s->Xspeed *= -1.0f;
//	}
//	else if (s->sprite->x < (bX_l + (radius/2)) && (s->Xspeed < 0))
//	{
//		s->Xspeed *= -1.0f;
//	}
//	if (s->sprite->y > (bY_t - (radius/2)) && (s->Yspeed > 0))
//	{
//		s->Yspeed *= -1.0f;
//	}
//	else if (s->sprite->y < (bY_b + (radius/2)) && (s->Yspeed < 0))
//	{
//		s->Yspeed *= -1.0f;
//	}
//	s->sprite->translate = glm::translate(s->sprite->translate, glm::vec3(s->Xspeed, s->Yspeed, 0.0f));
//	s->sprite->x += s->Xspeed;
//	s->sprite->y += s->Yspeed;
//}
//
////float randomPosition()
////{
////	int Xsign = rand() % 1;
////	int Ysign = rand() % 1;
////}
//
//void handleInput()
//{
//	//*****************************
//		//SDL handled input
//		//Any input to the program is done here
//
//	if (SDL_PollEvent(&event))
//	{
//		if (event.type == SDL_QUIT)
//		{
//			windowOpen = false;
//		}
//		if (event.type == SDL_WINDOWEVENT)
//		{
//			switch (event.window.event)
//			{
//			case SDL_WINDOWEVENT_RESIZED:
//				std::cout << "Window resized w:" << w << " h:" << h << std::endl;
//				SDL_GetWindowSize(win, &w, &h);
//				if ((aspect*h)<w)
//				{
//					newwidth = h * aspect;
//					left = (w - newwidth) / 2;
//					glViewport(left, 0, newwidth, h);
//				}
//				else
//				{
//					newheight = w * (1/aspect);
//					up = (h - newheight) / 2;
//					glViewport(0, up, w, newheight);
//				}
//				//SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
//				break;
//				
//
//			default:
//				break;
//			}
//		}
//		
//		if (event.type == SDL_KEYDOWN)
//		{
//			float tempX; //used to store random x co-ord when teleporting
//			float tempY; //used to store random y co-ord when teleporting
//			switch (event.key.keysym.sym)
//			{
//				
//			case SDLK_RSHIFT:
//				if (has_Shot)
//				{
//					projectile = new Shot(0.0f, 0.0f, angle);
//					catchImmune = true;
//					projectile->sprite->setBuffers();
//					projectile->sprite->translate=glm::translate(translate, glm::vec3(0.0f, 0.0f, 0.0f)); //apparently this line is crucial no idea why
//					projectile->sprite->x += player->x;
//					projectile->sprite->y += player->y;
//					has_Shot = false;
//				}
//				break;
//
//			case SDLK_SPACE:
//				tempX = (float)(rand() % ((int)bX_r * 100) + 1) / 100.0f;
//				tempY = (float)(rand() % ((int)bY_t * 100) + 1) / 100.0f;
//				translate=glm::translate(glm::mat4(1.0f), glm::vec3(tempX, tempY, 0.0f));
//				player->x += tempX;
//				player->y += tempY;
//				break;
//			case SDLK_UP:
//				translate = glm::translate(translate, glm::vec3((float)cos(angle)*0.08f, (float)sin(angle)*0.08f, 0.0f));
//				player->x += (float)cos(angle)*0.08f;
//				player->y += (float)sin(angle)*0.08f;
//				break;
//			case SDLK_DOWN:
//				translate = glm::translate(translate, -glm::vec3((float)sin(glm::radians(90.0f) - angle)*0.04f, (float)cos(glm::radians(90.0f) - angle)*0.04f, 0.0f));
//				player->x += -((float)sin(glm::radians(90.0f) - angle)*0.04f);
//				player->y += -((float)cos(glm::radians(90.0f) - angle)*0.04f);
//				break;
//			case SDLK_LEFT:
//				angle += glm::radians(10.0f);
//				rotate = glm::rotate(rotate,glm::radians(10.0f), glm::vec3(0, 0, 1));
//				break;
//			case SDLK_RIGHT:
//				angle -= glm::radians(10.0f);
//				rotate = glm::rotate(rotate, glm::radians(-10.0f) , glm::vec3(0, 0, 1));
//				break;
//			case SDLK_f:
//				if (isFullScreen)
//				{
//					SDL_SetWindowFullscreen(win, 0);
//					isFullScreen = false;
//				}
//				else if (!isFullScreen)
//				{
//					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
//					isFullScreen = true;
//				}
//				break;
//			}
//		}
//	}
//}
//
//
//
//#endif
//#endif
//#endif
//#endif