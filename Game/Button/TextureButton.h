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
    Vec2 center_m;
    double scale_m;
protected:
    static Shape textureRoundRect(Vec2 center, Texture texture, double scale);
public:
    TextureButton(Vec2 center, String texture, std::function<void(void)> handler);
    TextureButton(Vec2 center, String texture, double scale, std::function<void(void)> handler);
    TextureButton(Vec2 center, Texture texture, std::function<void(void)> handler);
    TextureButton(Vec2 center, Texture texture, double scale, std::function<void(void)> handler);
    virtual ~TextureButton() = default;
    void draw()const override;
};

