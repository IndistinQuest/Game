#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<memory>
#include<map>
#include"..\GameData.h"
#include"..\..\Button\ButtonInterface.h"
#include"..\..\Drawable\DrawableList.h"
#include"..\..\TextView\TextView.h"
#include"..\..\Data\EnemyData.h"
#include"..\..\Data\DataManager.h"

class BattleSceneObject;
class BattleSceneButton;
class PictureObject;

class Battle : public SceneManager<String, GameData>::Scene {
public:
	Battle();
	~Battle();
	void init()override;
	void update()override;
	void draw()const override;

private:
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, String  name, int layer);

	void Battle::newEnemy();	

private:
	int round_m;
	int time_m;

	//enemy
	EnemyData enemy_m;
	DataManager dataManager_m;
	std::shared_ptr<PictureObject> enemyPic_m;

	// objects
	std::multimap<String, std::shared_ptr<BattleSceneObject>> objects;
	std::multimap<String, std::shared_ptr<BattleSceneButton>> buttons;
	DrawableList drawList_m;

	std::shared_ptr<TextView> message_m;

	const String assetPath = L"../../Asset/";

	// state
	enum BattleState { win, lose, select };
	BattleState state_m;

	//const int tx = 5;
	//const int ty = 5;

	//const int roundWidth = 200;
	//const int timeWidth = 200;
	//const int mesWidth = Window::Width() - (tx * 4) - roundWidth - timeWidth;
};