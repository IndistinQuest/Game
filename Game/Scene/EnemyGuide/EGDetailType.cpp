#include "EGDetailType.h"
using namespace scene::enemyGuide;

/*
const double EGDetailType::NEXT_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::NEXT_BUTTON_HEIGHT = 0.1*H;
const double EGDetailType::PREVIOUS_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::PREVIOUS_BUTTON_HEIGHT = 0.1*H;
const double EGDetailType::LIST_BUTTON_WIDTH = 0.1*W;
const double EGDetailType::LIST_BUTTON_HEIGHT = 0.1*H;
*/
const double EGDetailType::TARGET_INFORMATION_WIDTH = 0.6*W;

const double EGDetailType::TARGET_SCALE = 0.3;
const int EGDetailType::FONT_SIZE = 16;

const int EGDetailType::TEXT_SPEED = 1;

const Point EGDetailType::POS_NEXT_BUTTON = Point(W - 150, 0.5*H);
const Point EGDetailType::POS_PREVIOUS_BUTTON = Point(150, 0.5*H);
const Point EGDetailType::POS_LIST_BUTTON = Point(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y - 150);
const Point EGDetailType::POS_TARGET = Point(0.2*W, 0.2*H);
const Point EGDetailType::POS_TARGET_NAME = Point(POS_PREVIOUS_BUTTON.x + 100, POS_PREVIOUS_BUTTON.y - 60);
const Point EGDetailType::POS_TARGET_MESSAGE = Point(POS_TARGET_NAME.x, POS_TARGET_NAME.y + 60);
const Point EGDetailType::POS_COLLECT_ANSWER = Point(POS_TARGET_NAME.x, POS_TARGET_MESSAGE.y + 120);
const Point EGDetailType::POS_DESCRIPTION = Point(POS_TARGET_NAME.x, POS_COLLECT_ANSWER.y + 60);

void EGDetailType::init() 
{
	ButtonManager::clearAll();
	ButtonManager::update();

	cursorID_m = 1;

	targetNameFont_m = Font(FONT_SIZE);
	targetMessageFont_m = Font(FONT_SIZE);
	collectAnswerFont_m = Font(FONT_SIZE);
	descriptionFont_m = Font(FONT_SIZE);

	backGround_m = std::make_shared<RollBackGround>(L"./Asset/enemies_graphic.jpg");
	for (int i = 1; i < KIND_OF_ENEMIES; ++i)
	{
		std::shared_ptr<uhhyoi::DrawableTexture> targetGraphic = std::make_shared<uhhyoi::DrawableTexture>(Texture(Format(L"./Asset/EnemyGraphics/", i, L".png")).scale(TARGET_SCALE), POS_TARGET);
		targetGraphics_m.add(targetGraphic, i);
	}

	goToNext_m = [this]() {this->nextTarget(); };
	backToPrevious_m = [this]() {this->previousTarget(); };
	backToList_m = [this]() {(this->*&Scene::changeScene)(L"EGListType", 500, false); };
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); };


	homeButton_m = std::make_shared<TextureButton>(Vec2(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y), L"./Asset/title_button_resize.png", backToTitle_m);
	nextButton_m = std::make_shared<TextureButton>(Vec2(POS_NEXT_BUTTON.x, POS_NEXT_BUTTON.y), L"./Asset/right_button_resize.png", goToNext_m);
	previousButton_m = std::make_shared<TextureButton>(Vec2(POS_PREVIOUS_BUTTON.x, POS_PREVIOUS_BUTTON.y), L"./Asset/left_button_resize.png", backToPrevious_m);
	backToListButton_m = std::make_shared<TextureButton>(Vec2(POS_LIST_BUTTON.x, POS_LIST_BUTTON.y), L"./Asset/back_button_resize.png", backToList_m);

	ButtonManager::add(homeButton_m);
	ButtonManager::add(nextButton_m);
	ButtonManager::add(previousButton_m);
	ButtonManager::add(backToListButton_m);

	nameTextView_m = std::make_shared<TextView>(L"", POS_TARGET_NAME, TARGET_INFORMATION_WIDTH, 2, targetNameFont_m, TEXT_SPEED, Palette::Black);
	messageTextView_m = std::make_shared<TextView>(L"", POS_TARGET_MESSAGE, TARGET_INFORMATION_WIDTH, 3, targetMessageFont_m, TEXT_SPEED, Palette::Black);
	answerTextView_m = std::make_shared<TextView>(L"", POS_COLLECT_ANSWER, TARGET_INFORMATION_WIDTH, 2, collectAnswerFont_m, TEXT_SPEED, Palette::Black);
	descriptionTextView_m = std::make_shared<TextView>(L"", POS_DESCRIPTION, TARGET_INFORMATION_WIDTH, 4, descriptionFont_m, TEXT_SPEED, Palette::Black);

}
void EGDetailType::update()
{
	nameTextView_m->update();
	messageTextView_m->update();
	answerTextView_m->update();
	descriptionTextView_m->update();
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
	
	nameTextView_m->draw();
	messageTextView_m->draw();
	answerTextView_m->draw();
	descriptionTextView_m->draw();
}

void EGDetailType::nextTarget()
{
	cursorID_m = (cursorID_m+1)%(KIND_OF_ENEMIES+1);
	target_m = dataManager_m.getEnemy(cursorID_m);

	nameTextView_m->setNewText(L"モンスター名\n" + target_m.name_m);
	messageTextView_m->setNewText(L"倒れた時のセリフ\n" + target_m.messages_m.onPlayerWon_m);
	answerTextView_m->setNewText(L"正解\n" + target_m.collectAnswer_m);
	descriptionTextView_m->setNewText(L"モンスターの説明\n" + target_m.description_m);
}

void EGDetailType::previousTarget()
{
	cursorID_m = (cursorID_m > 1) ? cursorID_m-1 : cursorID_m;
	target_m = dataManager_m.getEnemy(cursorID_m);
	nameTextView_m->setNewText(L"モンスター名\n" + target_m.name_m);
	messageTextView_m->setNewText(L"倒れた時のセリフ\n" + target_m.messages_m.onPlayerWon_m);
	answerTextView_m->setNewText(L"正解\n" + target_m.collectAnswer_m);
	descriptionTextView_m->setNewText(L"モンスターの説明\n" + target_m.description_m);
}
