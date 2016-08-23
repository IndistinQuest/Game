#include "EGListType.h"

using namespace scene::enemyGuide;

const double EGListType::W = 1280;
const double EGListType::H = 720;
const Point EGListType::POS_HEADING = Point(0.5*W, 0.2*H);
const Point EGListType::POS_HOME_BUTTON = Point(0.8*W, 0.8*H);

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
	int numOfEnemies = dataManager_m.getNumOfEnemies();
	for (int i = 0; i < numOfEnemies; ++i) {
		jumpaku::DrawableTxture icon();
		icons_m.add(std::make_shared<jumpaku::DrawableTxture>(Format(L"../../Assets/EnemyGraphics/", i, L".png"), Point(0, 0)), i);
	}
}

void EGListType::update()
{

}

void EGListType::draw() const
{
	title_m.draw(POS_HEADING, Palette::Orange);
	homeButton_m->draw();
}
