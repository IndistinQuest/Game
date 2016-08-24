#include "MyDrawableTexture.h"



MyDrawableTexture::MyDrawableTexture(String fileNumber, Point center)
	:MyDrawableTexture(Texture(fileNumber), center)
{}

MyDrawableTexture::MyDrawableTexture(Texture texture, Point center)
	: textureR_m(texture.flip()),
	center_m(center)
{}

MyDrawableTexture::MyDrawableTexture(TextureRegion textureR, Point center)
	: textureR_m(textureR),
	center_m(center)
{}



void MyDrawableTexture::draw() const
{
	textureR_m.drawAt(center_m);
	
}
