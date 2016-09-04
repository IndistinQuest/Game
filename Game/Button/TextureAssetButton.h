#pragma once

#include"TextureButton.h"
#include<Siv3D.hpp>

class TextureAssetButton :
    public TextureButton
{
public:
    TextureAssetButton(Vec2 center, String name, std::function<void(void)> handler);
    TextureAssetButton(Vec2 center, String name, double scale, std::function<void(void)> handler);
    virtual ~TextureAssetButton() = default;
};

