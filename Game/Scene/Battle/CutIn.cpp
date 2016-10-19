#include "CutIn.h"
using namespace scene::battle;

CutIn::CutIn() : pos_m(Window::Center()) {
	isHide = true;
};
CutIn::~CutIn() {};
void CutIn::init() {
	alpha_m = 100;
	scale_m = 10.0;
	pos_m = Window::Center();
	state_m = State::in;
	isHide = false;
}
void CutIn::hide() {
	isHide = true;
}
void CutIn::update(){

	if (isHide)return;

	if (alpha_m < 255) alpha_m += 5;

	switch (state_m)
	{
	case State::in:
		if (scale_m > LAST_SCALE) {
			scale_m -= 0.3;
		}
		else {
			scale_m = LAST_SCALE;
			state_m = State::move;
		}
		break;
	case State::center:
		break;
	case State::move:
	{
		const int spd = 10;

		Vec2 v(END_POS - pos_m);
		if (v.length() < spd) {
			pos_m = END_POS;
		}
		else {
			v.setLength(spd);
			pos_m.moveBy(v.asPoint());
		}
		break;
	}
	case State::moved:
		break;
	default:
		break;
	}
};
void CutIn::draw()const{
	if (!isHide) {
		TextureAsset(L"CutInEffect").scale(scale_m).drawAt(pos_m, Color(Palette::White).setAlpha(static_cast<int>(alpha_m)));
	}
}
