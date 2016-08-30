#pragma once
#include "../../Drawable/Drawable.h"

namespace uhhyoi {
	class DrawableTexture : public Drawable
	{
		TextureRegion textureR_m;
		Point center_m;
	public:
		void draw()const override;
		DrawableTexture(String fileNumber, Point center);
		DrawableTexture(Texture textue, Point center);
		DrawableTexture(TextureRegion textureR, Point center);
		~DrawableTexture() = default;
	};
}

