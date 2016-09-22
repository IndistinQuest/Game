#include "EGListType.h"

using namespace scene::enemyGuide;

const double EGListType::W = 1280;
const double EGListType::H = 720;
const Point EGListType::POS_HEADING = Point(0.45*W, 0.2*H);
const Point EGListType::POS_HOME_BUTTON = Point(0.85*W, 0.2*H);
const Point EGListType::POS_TERMINATE_BUTTON = Point(0.1*W, 0.15*H);
const int EGListType::KIND_OF_ENEMIES = 30;
const double EGListType::LIST_MARGIN = 20;
const double EGListType::LIST_BORDER = 0.3*H;
const int EGListType::LIST_ROW = 6;
const int EGListType::LIST_COL = 5;
const double EGListType::ICON_W = (W - (LIST_ROW+1)*LIST_MARGIN) / LIST_ROW;
const double EGListType::ICON_H = (H - LIST_BORDER - (LIST_COL + 1) * LIST_MARGIN) / LIST_COL;
const double EGListType::ICON_MAGNIFICATION = 0.25;


void EGListType::init()
{
	ButtonManager::clearAll();
	ButtonManager::update();
	
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); SoundAsset(L"enemies_bgm").stop();};
	terminateAll_m = [this]() {dataManager_m.clearSaveDate(); SoundAsset(L"enemies_decide").play(); };

	homeButton_m = std::make_shared<TextureAssetButton>(Vec2(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y), L"title_button", backToTitle_m);
	terminateButton_m = std::make_shared<RoundRectTextButton>(POS_TERMINATE_BUTTON.x, POS_TERMINATE_BUTTON.y, 30, 30, 122,  L"a", terminateAll_m);

	backGround_m = std::make_shared<RollBackGround>(L"firstEnemiesBackGround", L"secondEnemiesBackGround");

	ButtonManager::add(homeButton_m);
	ButtonManager::add(terminateButton_m);
	for (int i = 1; i <= KIND_OF_ENEMIES; ++i) {
		jumpToDetail_m = [this, i]() {(this->*&Scene::changeScene)(L"EGDetailType", 500, false); EGDetailType::changeTarget(i); SoundAsset(L"enemies_decide").play(); };
		if (dataManager_m.getSaveData(i).isDefeated_m)
		{
			std::shared_ptr<TextureAssetButton> icon = std::make_shared<TextureAssetButton>(Vec2(iconX(i), iconY(i)), Format(L"Enemy", i), ICON_MAGNIFICATION, jumpToDetail_m);
			icons_m.push_back(icon);
			ButtonManager::add(icon);
			
		}
		else
		{
			std::shared_ptr<DrawableAssetTexture> icon = std::make_shared<DrawableAssetTexture>(Format(L"ShadowEnemy", i), Point(iconX(i), iconY(i)), 0.1);
			shadows_m.add(icon, i);
		}
		
	}
	SoundAsset(L"enemies_bgm").play();
}

void EGListType::update()
{
	backGround_m->update();
}

void EGListType::draw() const
{
	backGround_m->draw();
	graphics_m.drawAll();
	title_m.draw(POS_HEADING);
	homeButton_m->draw();
	terminateButton_m->draw();
	shadows_m.drawAll();
	std::for_each (icons_m.begin(), icons_m.end(), [](std::shared_ptr<TextureAssetButton> b) {b->draw(); });
}

double EGListType::iconX(int i)
{
	int currentRow = (i-1) % LIST_ROW + 1;
	return currentRow * LIST_MARGIN + ((double)currentRow - 0.5) * ICON_W;
}

double EGListType::iconY(int i)
{
	int currentCol = (i-1) / LIST_ROW + 1;
	return currentCol * LIST_MARGIN + ((double)currentCol - 0.5) * ICON_H + LIST_BORDER;
}
