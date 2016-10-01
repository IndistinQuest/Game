#pragma once

#include<Siv3D.hpp>
#include"Drawable.h"

class DrawableAssetTexture : public Drawable
{
    String name_m;
    Vec2 const center_m;
    double scale_m;
public:
    void draw()const override;
    DrawableAssetTexture(String name, Vec2 center);
    DrawableAssetTexture(String name, Vec2 center, double scale);
    virtual ~DrawableAssetTexture() = default;
};