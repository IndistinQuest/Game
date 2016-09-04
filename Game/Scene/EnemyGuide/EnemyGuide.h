#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Heading.h"
#include "DrawableTexture.h"
#include "Heading.h"
#include "../../Drawable/DrawableList.h"
#include "../../Drawable/DrawableTxture.h"
#include "../../Button/ButtonManager.h"
#include "../../Button/RoundRectButton.h"
#include "../../Button/TextureButton.h"
#include "DrawableTexture.h"
#include "RollBackGround.h"
#include "../../Data/DataManager.h"


class EnemyGuide
{
protected:
	static const double W;
	static const double H;
	static const double HOME_BUTTON_WIDTH;
	static const double HOME_BUTTON_HEIGHT;
	static const Point POS_HEADING;
	static const Point POS_HOME_BUTTON;
	static const int KIND_OF_ENEMIES;

	const Heading title_m;

	DataManager dataManager_m;

	DrawableList graphics_m;
	std::function<void(void)> backToTitle_m;
	std::shared_ptr<TextureButton> homeButton_m;
	std::shared_ptr<RollBackGround> backGround_m;
public:
	EnemyGuide();
	~EnemyGuide();
};

