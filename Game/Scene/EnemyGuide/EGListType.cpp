#include "EGListType.h"

using namespace scene::enemyGuide;

const double EGListType::W = 1280;
const double EGListType::H = 720;
const Point EGListType::POS_HEADING = Point(0.5*W, 0.2*H);
const Point EGListType::POS_HOME_BUTTON = Point(0.8*W, 0.2*H);
const int EGListType::KIND_OF_ENEMIES = 30;
const double EGListType::LIST_MARGIN = 20;
const double EGListType::LIST_BORDER = 0.3*H;
const int EGListType::LIST_ROW = 6;
const int EGListType::LIST_COL = 5;
const double EGListType::ICON_W = (W - (LIST_ROW+1)*LIST_MARGIN) / LIST_ROW;
const double EGListType::ICON_H = (H - LIST_BORDER - (LIST_COL + 1) * LIST_MARGIN) / LIST_COL;


void EGListType::init()
{
	ButtonManager::clearAll();
	ButtonManager::update();
	
	backToTitle_m = [this]() {(this->*&Scene::changeScene)(L"Title", 500, false); };
	homeButton_m = std::make_shared<TextureButton>(Vec2(POS_HOME_BUTTON.x, POS_HOME_BUTTON.y), L"./Asset/title_button_resize.png", backToTitle_m);
	backGround_m = std::make_shared<RollBackGround>(L"./Asset/enemies_graphic.jpg");

	ButtonManager::add(homeButton_m);
	for (int i = 1; i <= KIND_OF_ENEMIES; ++i) {
		std::shared_ptr<Drawable> icon = std::make_shared<uhhyoi::DrawableTexture>(Texture(Format(L"./Asset/EnemyGraphics/", i, L".png")).scale(0.1), Point(iconX(i), iconY(i)));
		graphics_m.add(icon, i);
	}
}

void EGListType::update()
{
	backGround_m->update();
}

void EGListType::draw() const
{
	backGround_m->draw();
	graphics_m.drawAll();
	title_m.draw(POS_HEADING, Palette::Orange);
	homeButton_m->draw();
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
