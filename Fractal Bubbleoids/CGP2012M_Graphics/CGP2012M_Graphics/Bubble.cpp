#include "Bubble.h"



Bubble::Bubble(float radius, float Xcoord, float Ycoord)
{
	sprite = new CircleTexture(radius, Xcoord, Ycoord);
}


Bubble::~Bubble()
{
	delete sprite;
}
