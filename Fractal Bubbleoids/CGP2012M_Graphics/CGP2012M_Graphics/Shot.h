#pragma once
#include "Model.h"

class Shot
{
public:
	Model* sprite;; //the shot sprite
	float speed = 0.05f;
	float Xspeed;
	float Yspeed;

	Shot(float Xcoord, float Ycoord, float angle)
	{
		
		sprite = new Model(Xcoord, Ycoord, "..//..//Assets//Models//blenderSphere.obj", "..//..//Assets//Textures//projectile.png");
		sprite->scale = glm::mat4(1.0f);

		sprite->scale = glm::scale(sprite->scale, glm::vec3(0.2f, 0.2f, 0.2f));

		Xspeed = cos(angle)*speed;
		Yspeed = sin(angle)*speed;
		std::cout << "angle: " << angle << " xspeed: " << Xspeed << "yspeed: " << Yspeed << std::endl;
	}

	void setBuffers()
	{
		sprite->setBuffers();
	}

	~Shot()
	{
		delete sprite;
	}
};