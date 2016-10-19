#include"PictureObject.h"
using namespace scene::battle;

PictureObject::PictureObject(String assetName, double scale, Point pos) :pos(pos), defaultScale(scale) {
	changeTexture(assetName);
	init();
}
void PictureObject::update(){
	if (isFadeIn && alpha < 255) {
		alpha += FADE_IN;
		if (alpha > 255) { alpha = 255; }

		if (isBigger) {
			scale += FADE_IN / 255;
			if (scale > defaultScale) { scale = defaultScale; }
		}
	}
	if (isFadeOut && alpha > 0) {
		alpha -= FADE_OUT;
		if (alpha < 0) { alpha = 0; }

		if (isRoolAndSmall) {
			scale -= FADE_OUT / 255;
			if (scale < 0) { scale = 0; }

			rad += 0.1;
		}
	}
	if (isExpansion && scale <=MAX_SCALE) {
		scale += (MAX_SCALE - SCALE) / 10;
		if (scale > MAX_SCALE) { scale = MAX_SCALE; }
	}
}
// V‚µ‚¢‰æ‘œ‚É•Ï‚¦‚é
// String text ‰æ‘œ‚Ì–¼‘O
void PictureObject::changeTexture(String assetname) {
	aseetName = assetname;
	setFadeIn();
}
void PictureObject::draw()const{
	Point drawPos = pos + Point(Math::Cos(System::FrameCount()), 0);
	TextureAsset(aseetName).scale(scale).rotate(rad).drawAt(drawPos, Color(Palette::White).setAlpha(static_cast<int>(alpha)));
}
void PictureObject::init() {
	scale = defaultScale;
	alpha = 255;
	isFadeOut = false;
	isFadeIn = false;
	isExpansion = false;
	rad = 0;
	isRoolAndSmall = false;
	isBigger = false;
}
void PictureObject::setFadeOut() {
	isFadeOut = true;
	isFadeIn = false;
}
void PictureObject::setRoolAndSmall() {
	isRoolAndSmall = true;
}
void PictureObject::setBigger() {
	scale = 0.0;
	isBigger = true;
}
void PictureObject::setFadeIn() {
	init();
	isFadeIn = true;
	isFadeOut = false;
	alpha = 0;
}
bool PictureObject::isDraw() {
	if (alpha > 0) { return true; }
	else { return false; }
}
void PictureObject::setExpansion() {
	isExpansion = true;
}
