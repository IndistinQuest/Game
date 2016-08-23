#include "Heading.h"

const String Heading::sentence_m = L"ÉÇÉìÉXÉ^Å[ê}ä”";


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
