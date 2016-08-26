#include "EGDetailType.h"
using namespace scene::enemyGuide;

const Point EGDetailType::POS_NEXT_BUTTON = Point(0.9*W, 0.5*H);
const Point EGDetailType::POS_PREVIOUS_BUTTON = Point(0.1*W, 0.5*H);
const Point EGDetailType::POS_LIST_BUTTON = Point(0.3*W, 0.8*H);
const Point EGDetailType::POS_TARGET = Point(0.5*W, 0.8*H);

void EGDetailType::init() 
{
	ButtonManager::clearAll();
	ButtonManager::update();

	cursorID_m = 1;
	
	backGround_m = std::make_shared<RollBackGround>(L"./Asset/enemies_graphic.jpg");
	for (int i = 1; i < KIND_OF_ENEMIES; ++i)
	{
		std::shared_ptr<uhhyoi::DrawableTexture> targetGraphic = std::make_shared<uhhyoi::DrawableTexture>(Texture(Format(L"./Asset/EnemyGraphics/", i, L".png")).scale(0.5), POS_TARGET);
		targetGraphics_m.add(targetGraphic, i);
	}

	goToNext_m = [this]() {this->nextTarget(); };
	backToPrevious_m = [this]() {this->previousTarget(); };
	backToList_m = [this]() {(this->*&Scene::changeScene)(L"EGListType", 500, false); };
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); };


	homeButton_m = std::make_shared<RoundRectTextButton>(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y, 0.1*W, 0.1*H, 176, L"タイトルに戻る", backToTitle_m);
	nextButton_m = std::make_shared<RoundRectTextButton>(POS_NEXT_BUTTON.x, POS_NEXT_BUTTON.y, 0.1*W, 0.1*H, 176, L"次", goToNext_m);
	previousButton_m = std::make_shared<RoundRectTextButton>(POS_PREVIOUS_BUTTON.x, POS_PREVIOUS_BUTTON.y, 0.1*W, 0.1*H, 176, L"戻る", backToPrevious_m);
	backToListButton_m = std::make_shared<RoundRectTextButton>(POS_LIST_BUTTON.x, POS_LIST_BUTTON.y, 0.1*W, 0.1*H, 176, L"リストへ", backToList_m);

	ButtonManager::add(homeButton_m);
	ButtonManager::add(nextButton_m);
	ButtonManager::add(previousButton_m);
	ButtonManager::add(backToListButton_m);

}
void EGDetailType::update()
{
	target_m = dataManager_m.getEnemy(cursorID_m);
	backGround_m->update();
}
void EGDetailType::draw() const 
{
	backGround_m->draw();
	graphics_m.drawAll();
	title_m.draw(POS_HEADING, Palette::Orange);
	
	homeButton_m->draw();
	nextButton_m->draw();
	previousButton_m->draw();
	backToListButton_m->draw();

	targetGraphics_m.drawLayer(cursorID_m);
}

void EGDetailType::nextTarget()
{
	cursorID_m++;
}

void EGDetailType::previousTarget()
{
	cursorID_m--;
}
