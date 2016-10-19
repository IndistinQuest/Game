#include "WindowAndText.h"
using namespace scene::battle;

WindowAndText::WindowAndText(Point center, String textureAssetName, Color c) : center_m(center), textureAssetName_m(textureAssetName), strColor_m(c) {};
void WindowAndText::update(){};
void WindowAndText::setText(String text) {
	str_m = text;
}
void WindowAndText::draw()const{
	TextureAsset(textureAssetName_m).drawAt(center_m);
	FontAsset(L"BattleSceneFont").drawCenter(str_m, center_m, strColor_m);
}
