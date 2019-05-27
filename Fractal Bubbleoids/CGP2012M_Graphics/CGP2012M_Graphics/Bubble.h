#pragma once
#include "Model.h"

class Bubble
{
public:
	Model* sprite; //the bubble sprite
	float Xspeed;
	float Yspeed;

	Bubble(float Xcoord, float Ycoord, float s)
	{
		if (rand() % 2 == 0)
		{
			Xspeed = s;
		}
		else
		{
			Xspeed = -s;
		}
		if (rand() % 2 == 0)
		{
			Yspeed = s;
		}
		else
		{
			Yspeed = -s;
		}
		sprite = new Model(Xcoord, Ycoord, "..//..//Assets//Models//blenderSphere.obj", "..//..//Assets//Textures//bubble.png");
	
		sprite->scale = glm::scale(sprite->scale, glm::vec3(0.4f, 0.4f, 0.4f));
	}

	void setBuffers()
	{
		sprite->setBuffers();
	}

	~Bubble()
	{
		delete sprite;
	}
};