#include "Heading.h"

const String Heading::sentence_m = L"�����X�^�[�}��";


Heading::Heading()
{
	headingSentence_m = Font(30);
}


Heading::~Heading()
{
}

void Heading::draw(Point position, Color color) const
{
	headingSentence_m.draw(sentence_m, position, color);
}
