#pragma once
#include <Siv3D.hpp>
class RollBackGround
{
private:
	const static double W;
	const static double H;
	const static int ROLL_SPEED;

	Point fPoint_m;
	Point sPoint_m;

	String firstAssetName_m;
	String secondAssetName_m;
public:
	RollBackGround(String firstAssetName, String secondAssetName);
	~RollBackGround();

	void update();
	void draw() const;
};

