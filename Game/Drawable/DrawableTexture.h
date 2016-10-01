#pragma once

#include<Siv3D.hpp>
#include"Drawable.h"

namespace jumpaku {

class DrawableTexture : public Drawable
{
    Texture texture_m;
    Vec2 center_m;
    double scale_m;
public:
    void draw()const override;
    DrawableTexture(Texture texture, Vec2 center);
    DrawableTexture(Texture texture, Vec2 center, double scale);
    ~DrawableTexture() = default;
};

}
