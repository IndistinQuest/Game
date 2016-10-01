#pragma once
#include<Siv3D.hpp>

class Heading
{
private:
	String headingAssetName_m;
public:
	Heading();
	~Heading();
	void draw(Point position) const;
};

