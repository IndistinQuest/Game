#include "TextureAssetButton.h"


static Shape makeShape(Vec2 center, String name, double scale)
{
    Size wh = TextureAsset(name).size;
    return Shape(RoundRect(center.x - wh.x*scale / 2, center.y - wh.y*scale / 2, wh.x*scale, wh.y*scale, 5));
}

TextureAssetButton::TextureAssetButton(Vec2 center, String name, std::function<void(void)> handler)
    :TextureAssetButton(center, name, 1.0, handler)
{}


TextureAssetButton::TextureAssetButton(Vec2 center, String name, double scale, std::function<void(void)> handler)
    :LambdaButton(makeShape(center, name, scale), handler),
    name_m(name),
    center_m(center),
    scale_m(scale)
{}


void TextureAssetButton::draw()const
{
    switch (getState()) {
    case State::LEFT:
        TextureAsset(name_m).scale(scale_m).drawAt(center_m);
        break;
    case State::MOUSE_OVER:
        TextureAsset(name_m).scale(scale_m*1.03).drawAt(center_m);
        break;
    case State::PRESSED:
        TextureAsset(name_m).scale(scale_m*0.97).drawAt(center_m.movedBy(0, 2));
        break;
    case State::RELEASED:
        TextureAsset(name_m).scale(scale_m).drawAt(center_m);
        break;
    default:
        break;
    }
}