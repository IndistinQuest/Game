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
	TextureAsset(headingAssetName_m).drawAt(center);
}
