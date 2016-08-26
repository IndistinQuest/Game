#pragma once
#include <Siv3D.hpp>
class RollBackGround
{
private:
	const static double W;
	const static double H;
	const static double ROLL_SPEED;
	Texture firstBackGround_m;
	Texture secondBackGround_m;

	Point fPoint_m;
	Point sPoint_m;
public:
	RollBackGround(String backGroundURL);
	~RollBackGround();

	void update();
	void draw() const;
};

