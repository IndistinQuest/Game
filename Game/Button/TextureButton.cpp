#include "TextureButton.h"

Shape TextureButton::textureRoundRect(Vec2 center, Texture texture, double scale)
{
    Size wh = texture.size;
    return Shape(RoundRect(center.x - wh.x*scale / 2, wh.y*scale / 2, wh.x, wh.y, 5));
}

TextureButton::TextureButton(Vec2 center, String path, std::function<void(void)> handler)
    :TextureButton(center, Texture(path), handler)
{}

TextureButton::TextureButton(Vec2 center, String path, double scale, std::function<void(void)> handler)
    :TextureButton(center, Texture(path), scale, handler)
{}

TextureButton::TextureButton(Vec2 center, Texture texture, std::function<void(void)> handler)
    :TextureButton(center, texture, 1.0, handler)
{}

TextureButton::TextureButton(Vec2 center, Texture texture, double scale, std::function<void(void)> handler)
    :LambdaButton(textureRoundRect(center, texture, scale), handler),
    texture_m(texture),
    center_m(center),
    scale_m(scale)
{}

void TextureButton::draw()const
{
    switch (getState()) {
    case State::LEFT:
        texture_m.scale(scale_m).drawAt(center_m);
        break;
    case State::MOUSE_OVER:
        texture_m.scale(scale_m*1.03).drawAt(center_m);
        break;
    case State::PRESSED:
        texture_m.scale(scale_m*0.97).drawAt(center_m.movedBy(0, 2));
        break;
    case State::RELEASED:
        texture_m.scale(scale_m).drawAt(center_m);
        break;
    default:
        break;
    }
}