#pragma once

#include"TextureButton.h"
#include<Siv3D.hpp>

class TextureAssetButton :
    public LambdaButton,
    public Drawable
{
    Vec2 center_m;
    String name_m;
    double scale_m;
public:
    void draw()const override;
    TextureAssetButton(Vec2 center, String name, std::function<void(void)> handler);
    TextureAssetButton(Vec2 center, String name, double scale, std::function<void(void)> handler);
    virtual ~TextureAssetButton() = default;
};

