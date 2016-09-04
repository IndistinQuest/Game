#pragma once
#include "../../Drawable/Drawable.h"

namespace uhhyoi {
	class DrawableTexture : public Drawable
	{
		TextureRegion textureR_m;
		Point center_m;
		String assetName_m;
		double scalePercentage_m;
	public:
		void draw()const override;
		DrawableTexture(String assetName_m, Point center, double scalePercentage_m = 1.0);
		~DrawableTexture() = default;
	};
}

