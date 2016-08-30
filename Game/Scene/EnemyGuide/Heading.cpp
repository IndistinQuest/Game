#include "Heading.h"

const String Heading::sentence_m = L"ƒ‚ƒ“ƒXƒ^[}ŠÓ";


Heading::Heading()
{
	headingSentence_m = Font(30);
}


Heading::~Heading()
{
}

void Heading::draw(Point center, Color color) const
{

	Point edgePos = { center.x - sentence_m.length * 30 / 2, center.y - headingSentence_m.height / 2 };

	headingSentence_m.draw(sentence_m, edgePos, color);
}
