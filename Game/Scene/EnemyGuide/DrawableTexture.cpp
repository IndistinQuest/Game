#include "DrawableTexture.h"

using namespace uhhyoi;

DrawableTexture::DrawableTexture(String fileNumber, Point center)
	:DrawableTexture(Texture(fileNumber), center)
{}

DrawableTexture::DrawableTexture(Texture texture, Point center)
	: textureR_m(texture.flip()),
	center_m(center)
{}

DrawableTexture::DrawableTexture(TextureRegion textureR, Point center)
	: textureR_m(textureR),
	center_m(center)
{}



void DrawableTexture::draw() const
{
	textureR_m.drawAt(center_m);
	
}
