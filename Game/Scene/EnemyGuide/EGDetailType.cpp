#include "EGDetailType.h"
using namespace scene::enemyGuide;

const int EGDetailType::TARGET_INFORMATION_WIDTH = static_cast<const int>(0.6*W);

const double EGDetailType::TARGET_SCALE = 0.25;
const int EGDetailType::FONT_SIZE = 16;

const int EGDetailType::TEXT_SPEED = 1;

const Point EGDetailType::POS_NEXT_BUTTON = Point(W - 150, 0.5*H);
const Point EGDetailType::POS_PREVIOUS_BUTTON = Point(150, 0.5*H);
const Point EGDetailType::POS_LIST_BUTTON = Point(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y - 150);
const Point EGDetailType::POS_TARGET = Point(0.2*W, 0.22*H);
const Point EGDetailType::POS_TARGET_NAME = Point(POS_PREVIOUS_BUTTON.x + 100, POS_PREVIOUS_BUTTON.y - 60);
const Point EGDetailType::POS_TARGET_MESSAGE = Point(POS_TARGET_NAME.x, POS_TARGET_NAME.y + 60);
const Point EGDetailType::POS_COLLECT_ANSWER = Point(POS_TARGET_NAME.x, POS_TARGET_MESSAGE.y + 120);
const Point EGDetailType::POS_DESCRIPTION = Point(POS_TARGET_NAME.x, POS_COLLECT_ANSWER.y + 60);

int EGDetailType::cursorID_m = 1;

void EGDetailType::init() 
{
	ButtonManager::clearAll();
	ButtonManager::update();

	targetNameFont_m = Font(FONT_SIZE);
	targetMessageFont_m = Font(FONT_SIZE);
	collectAnswerFont_m = Font(FONT_SIZE);
	descriptionFont_m = Font(FONT_SIZE);

	backGround_m = std::make_shared<RollBackGround>(L"firstEnemiesBackGround", L"secondEnemiesBackGround");
	for (int i = 1; i <= KIND_OF_ENEMIES; ++i)
	{
		std::shared_ptr<DrawableAssetTexture> targetGraphic = std::make_shared<DrawableAssetTexture>(Format(L"Enemy", i), POS_TARGET, TARGET_SCALE);
		targetGraphics_m.add(targetGraphic, i);
	}

	goToNext_m = [this]() {this->nextTarget(); SoundAsset(L"enemies_move").play(); };
	backToPrevious_m = [this]() {this->previousTarget(); SoundAsset(L"enemies_move").play(); };
	backToList_m = [this]() {(this->*&Scene::changeScene)(L"EGListType", 500, false); SoundAsset(L"enemies_return").play(); };
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); SoundAsset(L"enemies_bgm").stop(); };


	homeButton_m = std::make_shared<TextureAssetButton>(Vec2(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y), L"title_button", backToTitle_m);
	nextButton_m = std::make_shared<TextureAssetButton>(Vec2(POS_NEXT_BUTTON.x, POS_NEXT_BUTTON.y), L"right_button", goToNext_m);
	previousButton_m = std::make_shared<TextureAssetButton>(Vec2(POS_PREVIOUS_BUTTON.x, POS_PREVIOUS_BUTTON.y), L"left_button", backToPrevious_m);
	backToListButton_m = std::make_shared<TextureAssetButton>(Vec2(POS_LIST_BUTTON.x, POS_LIST_BUTTON.y), L"back_button_resize", backToList_m);

	ButtonManager::add(homeButton_m);
	ButtonManager::add(nextButton_m);
	ButtonManager::add(previousButton_m);
	ButtonManager::add(backToListButton_m);

	nameTextView_m = std::make_shared<TextView>(L"", POS_TARGET_NAME, TARGET_INFORMATION_WIDTH, 2, targetNameFont_m, TEXT_SPEED, Palette::Black);
	messageTextView_m = std::make_shared<TextView>(L"", POS_TARGET_MESSAGE, TARGET_INFORMATION_WIDTH, 3, targetMessageFont_m, TEXT_SPEED, Palette::Black);
	answerTextView_m = std::make_shared<TextView>(L"", POS_COLLECT_ANSWER, TARGET_INFORMATION_WIDTH, 2, collectAnswerFont_m, TEXT_SPEED, Palette::Black);
	descriptionTextView_m = std::make_shared<TextView>(L"", POS_DESCRIPTION, TARGET_INFORMATION_WIDTH, 4, descriptionFont_m, TEXT_SPEED, Palette::Black);

	target_m = dataManager_m.getEnemy(cursorID_m);

	nameTextView_m->setNewText(L"モンスター名\n" + target_m.name_m);
	messageTextView_m->setNewText(L"倒れた時のセリフ\n" + target_m.messages_m.onPlayerWon_m);
	answerTextView_m->setNewText(L"正解\n" + target_m.collectAnswer_m);
	descriptionTextView_m->setNewText(L"モンスターの説明\n" + target_m.description_m);

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
	title_m.draw(POS_HEADING);
	
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
	cursorID_m = (cursorID_m >= 30) ? 1 : cursorID_m+1;
	target_m = dataManager_m.getEnemy(cursorID_m);

	if (dataManager_m.getSaveData(cursorID_m).isDefeated_m)
	{
		showData();
	}
	else
	{
		nextTarget();
	}
}
void EGDetailType::previousTarget()
{
	cursorID_m = (cursorID_m <= 1) ? 30 : cursorID_m-1;
	target_m = dataManager_m.getEnemy(cursorID_m);
	
	if(dataManager_m.getSaveData(cursorID_m).isDefeated_m)
	{
		showData();
	}
	else
	{
		previousTarget();
	}
}

void EGDetailType::changeTarget(int ID)
{
	cursorID_m = ID;
}

void EGDetailType::showData()
{
	nameTextView_m->setNewText(L"モンスター名\n" + target_m.name_m);
	messageTextView_m->setNewText(L"倒れた時のセリフ\n" + target_m.messages_m.onPlayerWon_m);
	answerTextView_m->setNewText(L"正解\n" + target_m.collectAnswer_m);
	descriptionTextView_m->setNewText(L"モンスターの説明\n" + target_m.description_m);
}
