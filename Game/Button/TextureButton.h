#pragma once

#include"LambdaButton.h"
#include"../Drawable/Drawable.h"
#include<Siv3D.hpp>

class TextureButton :
    public LambdaButton,
    public Drawable
{
private:
    Texture texture_m;
    String text_m;
    Vec2 center_m;

public:
    TextureButton(Vec2 center, String texture, std::function<void(void)> handler);
    TextureButton(Vec2 center, Texture texture, std::function<void(void)> handler);
    virtual ~TextureButton() = default;
    void draw()const override;
};

