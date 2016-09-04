#include "TextureAssetButton.h"

TextureAssetButton::TextureAssetButton(Vec2 center, String name, std::function<void(void)> handler)
    :TextureAssetButton(center, name, 1.0, handler)
{}


TextureAssetButton::TextureAssetButton(Vec2 center, String name, double scale, std::function<void(void)> handler)
    :TextureButton(center, TextureAsset(name), scale, handler)
{}
