#include "RollBackGround.h"

const double RollBackGround::W = 1280;
const double RollBackGround::H = 720;
const double RollBackGround::ROLL_SPEED = 5;


RollBackGround::RollBackGround(String backGroundURL)
{
	firstBackGround_m = Texture(backGroundURL);
	secondBackGround_m = Texture(backGroundURL);

	fPoint_m = Point(0, 0);
	sPoint_m = Point(W, 0);
}


RollBackGround::~RollBackGround()
{
}

void RollBackGround::update()
{
	fPoint_m.x -= ROLL_SPEED;
	sPoint_m.x -= ROLL_SPEED;

	if (fPoint_m.x <= -W)
	{
		fPoint_m.x = W;
	}
	if (sPoint_m.x <= -W)
	{
		sPoint_m.x = W;
	}
}

void RollBackGround::draw() const
{
	firstBackGround_m.draw(fPoint_m);
	secondBackGround_m.draw(sPoint_m);
}
