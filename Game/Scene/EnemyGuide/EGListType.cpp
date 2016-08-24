#include "EGListType.h"

using namespace scene::enemyGuide;

const double EGListType::W = 1280;
const double EGListType::H = 720;
const Point EGListType::POS_HEADING = Point(0.5*W, 0.2*H);
const Point EGListType::POS_HOME_BUTTON = Point(0.8*W, 0.8*H);
const int EGListType::KIND_OF_ENEMIES = 30;
const double EGListType::LIST_MARGIN = 20;
const double EGListType::LIST_BORDER = 0.3*H;
const int EGListType::LIST_ROW = 6;
const int EGListType::LIST_COL = 5;
const double EGListType::ICON_W = (W - (LIST_ROW+1)*LIST_MARGIN) / LIST_ROW;
const double EGListType::ICON_H = (H - LIST_BORDER - (LIST_COL + 1) * LIST_MARGIN) / LIST_COL;

/*
EGListType::EGListType()
{
	init();
}


EGListType::~EGListType()
{
}*/

void EGListType::init()
{
	ButtonManager::clearAll();
	ButtonManager::update();
	
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); };
	homeButton_m = std::make_shared<RoundRectTextButton>(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y, 0.1*W, 0.1*H, 176, L"ƒ^ƒCƒgƒ‹‚É–ß‚é", backToTitle_m);

	ButtonManager::add(homeButton_m);
	for (int i = 0; i < KIND_OF_ENEMIES; ++i) {
		jumpaku::DrawableTxture icon();
		icons_m.add(std::make_shared<jumpaku::DrawableTxture>(Format(L"../../Asset/EnemyGraphics/", i, L".png"), Point(iconX(i), iconY(i))), i);
	}
}

void EGListType::update()
{

}

void EGListType::draw() const
{
	title_m.draw(POS_HEADING, Palette::Orange);
	icons_m.drawAll();
	homeButton_m->draw();
}

double EGListType::iconX(int i)
{
	int currentRow = (i + 1) % (LIST_ROW + 1) + 1;
	return currentRow * LIST_MARGIN + ((double)currentRow - 0.5) * ICON_W;
}

double EGListType::iconY(int i)
{
	int currentCol = i / LIST_ROW + 1;
	return currentCol * LIST_MARGIN + ((double)currentCol - 0.5) * ICON_H + LIST_BORDER;
}
