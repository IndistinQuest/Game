#include "Heading.h"

Heading::Heading()
{
	headingAssetName_m = L"enemies_logo";
}


Heading::~Heading()
{
}

void Heading::draw(Point center) const
{

//	Point edgePos = { center.x - sentence_m.length * 30 / 2, center.y - headingSentence_m.height / 2 };
	TextureAsset(headingAssetName_m).drawAt(center);
}
