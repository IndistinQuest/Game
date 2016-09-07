#include "RollBackGround.h"

const double RollBackGround::W = 1280;
const double RollBackGround::H = 720;
const int RollBackGround::ROLL_SPEED = 5;


RollBackGround::RollBackGround(String firstAssetName, String secondAssetName)
{
	firstAssetName_m = firstAssetName;
	secondAssetName_m = secondAssetName;

	fPoint_m = Point(0.5*W, 0.5*H);
	sPoint_m = Point(1.5*W, 0.5*H);
}


RollBackGround::~RollBackGround()
{
}

void RollBackGround::update()
{
	fPoint_m.x -= ROLL_SPEED;
	sPoint_m.x -= ROLL_SPEED;

	if (fPoint_m.x <= static_cast<int>(-0.5*W))
	{
		fPoint_m.x = static_cast<int>(1.5*W);
	}
	if (sPoint_m.x <= static_cast<int>(-0.5*W))
	{
		sPoint_m.x = static_cast<int>(1.5*W);
	}
}

void RollBackGround::draw() const
{
	TextureAsset(firstAssetName_m).drawAt(fPoint_m);
	TextureAsset(secondAssetName_m).drawAt(sPoint_m);
}
