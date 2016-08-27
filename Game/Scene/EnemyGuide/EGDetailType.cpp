#include "EGDetailType.h"
using namespace scene::enemyGuide;

const double EGDetailType::NEXT_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::NEXT_BUTTON_HEIGHT = 0.1*H;
const double EGDetailType::PREVIOUS_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::PREVIOUS_BUTTON_HEIGHT = 0.1*H;
const double EGDetailType::LIST_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::LIST_BUTTON_HEIGHT = 0.1*H;

const double EGDetailType::TARGET_SCALE = 0.3;

const Point EGDetailType::POS_NEXT_BUTTON = Point(W-50-NEXT_BUTTON_WIDTH, 0.5*H);
const Point EGDetailType::POS_PREVIOUS_BUTTON = Point(50, 0.5*H);
const Point EGDetailType::POS_LIST_BUTTON = Point(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y - 20 - LIST_BUTTON_HEIGHT);
const Point EGDetailType::POS_TARGET = Point(0.2*W, 0.2*H);
const Point EGDetailType::POS_TARGET_NAME = Point(POS_PREVIOUS_BUTTON.x + PREVIOUS_BUTTON_WIDTH + 20, POS_PREVIOUS_BUTTON.y);
const Point EGDetailType::POS_TARGET_MESSAGE = Point(POS_TARGET_NAME.x, POS_TARGET_NAME.y + 60);
const Point EGDetailType::POS_COLLECT_ANSWER = Point(POS_TARGET_NAME.x, POS_TARGET_MESSAGE.y + 60);
const Point EGDetailType::POS_DESCRIPTION = Point(POS_TARGET_NAME.x, POS_COLLECT_ANSWER.y + 60);

void EGDetailType::init() 
{
	ButtonManager::clearAll();
	ButtonManager::update();

	cursorID_m = 1;

	targetName_m = Font(20);
	targetMessage_m = Font(20);
	collectAnswer_m = Font(20);
	description_m = Font(20);
	
	backGround_m = std::make_shared<RollBackGround>(L"./Asset/enemies_graphic.jpg");
	for (int i = 1; i < KIND_OF_ENEMIES; ++i)
	{
		std::shared_ptr<uhhyoi::DrawableTexture> targetGraphic = std::make_shared<uhhyoi::DrawableTexture>(Texture(Format(L"./Asset/EnemyGraphics/", i, L".png")).scale(TARGET_SCALE), POS_TARGET);
		targetGraphics_m.add(targetGraphic, i);
	}

	goToNext_m = [this]() { };
	backToPrevious_m = [this]() {this->previousTarget(&(this->cursorID_m)); };
	backToList_m = [this]() {(this->*&Scene::changeScene)(L"EGListType", 500, false); };
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); };


	homeButton_m = std::make_shared<RoundRectTextButton>(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y, HOME_BUTTON_WIDTH, HOME_BUTTON_HEIGHT, 176, L"タイトルに戻る", backToTitle_m);
	nextButton_m = std::make_shared<RoundRectTextButton>(POS_NEXT_BUTTON.x, POS_NEXT_BUTTON.y, NEXT_BUTTON_WIDTH, NEXT_BUTTON_HEIGHT, 176, L"次", goToNext_m);
	previousButton_m = std::make_shared<RoundRectTextButton>(POS_PREVIOUS_BUTTON.x, POS_PREVIOUS_BUTTON.y, PREVIOUS_BUTTON_WIDTH, PREVIOUS_BUTTON_HEIGHT, 176, L"戻る", backToPrevious_m);
	backToListButton_m = std::make_shared<RoundRectTextButton>(POS_LIST_BUTTON.x, POS_LIST_BUTTON.y, LIST_BUTTON_WIDTH, LIST_BUTTON_HEIGHT, 176, L"リストへ", backToList_m);

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

	targetName_m(target_m.name_m).draw(POS_TARGET_NAME, Palette::Darkturquoise);
	targetMessage_m(target_m.messages_m.onPlayerWon_m).draw(POS_TARGET_MESSAGE, Palette::Darkmagenta);
	collectAnswer_m(target_m.collectAnswer_m).draw(POS_COLLECT_ANSWER, Palette::Crimson);
	description_m(target_m.description_m).draw(POS_DESCRIPTION, Palette::Firebrick);
}

void EGDetailType::nextTarget(int* address)
{
	(*address)++;
}

void EGDetailType::previousTarget(int* address)
{
	(*address)--;
}
