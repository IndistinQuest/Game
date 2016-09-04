#include "DrawableTexture.h"

using namespace uhhyoi;

DrawableTexture::DrawableTexture(String assetName, Point center, double scalePercentage)
{
	assetName_m = assetName;
	center_m = center;
	scalePercentage_m = scalePercentage;
}



void DrawableTexture::draw() const
{
	TextureAsset(assetName_m).scale(scalePercentage_m).drawAt(center_m);
	
}
