#include"BattleSceneButton.h"
using namespace scene::battle;

BattleSceneButton::BattleSceneButton(Point pos, Size size, String textureAssetName, Color c)
	:BasicButton(Shape(Rect(pos, size))), size(size), pos(pos), center(pos + size / 2), textureAssetName_m(textureAssetName), color_m(c) {};
void BattleSceneButton::draw() const
{
	Point bPos = center;
	double mag = 1.0;
	switch (getState()) {
	case State::MOUSE_OVER:
		bPos.moveBy({ 0,-2 });
		mag = 1.01;
		break;
	case State::LEFT:
	case State::PRESSED:
	case State::RELEASED:
	default:
		break;
	}
	TextureAsset(textureAssetName_m).scale(mag).drawAt(bPos);
	FontAsset(L"BattleSceneFont").drawCenter(text_m, bPos, color_m);
}
void BattleSceneButton::setText(String text) {
	text_m = text;
}
void BattleSceneButton::update(){}
void BattleSceneButton::setStrColor(Color c) {
	color_m = c;
}
