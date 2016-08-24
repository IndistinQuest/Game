#pragma once
#include "../../Drawable/Drawable.h"
class MyDrawableTexture : public Drawable
{
	TextureRegion textureR_m;
	Point center_m;
public:
	void draw()const override;
	MyDrawableTexture(String fileNumber, Point center);
	MyDrawableTexture(Texture textue, Point center);
	MyDrawableTexture(TextureRegion textureR, Point center);
	~MyDrawableTexture() = default;
};

