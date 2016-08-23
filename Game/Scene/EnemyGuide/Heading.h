#pragma once
#include<Siv3D.hpp>

class Heading
{
private:
	Font headingSentence_m;
	static const String sentence_m;
public:
	Heading();
	~Heading();
	void draw(Point position, Color color) const;
};

