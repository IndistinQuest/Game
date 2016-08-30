#include "TextureButton.h"

TextureButton::TextureButton(Vec2 center, String path, std::function<void(void)> handler)
    :TextureButton(center, Texture(path), handler)
{}

TextureButton::TextureButton(Vec2 center, Texture texture, std::function<void(void)> handler)
    :LambdaButton(Shape(RoundRect(center.x-texture.width/2, center.y-texture.height/2, texture.width, texture.height, 5)), handler),
    texture_m(texture),
    center_m(center)
{}

void TextureButton::draw()const
{
    switch (getState()) {
    case State::LEFT:
        texture_m.drawAt(center_m);
        break;
    case State::MOUSE_OVER:
        texture_m.scale(1.03).drawAt(center_m);
        break;
    case State::PRESSED:
        texture_m.scale(0.97).drawAt(center_m.movedBy(0, 2));
        break;
    case State::RELEASED:
        texture_m.drawAt(center_m);
        break;
    default:
        break;
    }
}