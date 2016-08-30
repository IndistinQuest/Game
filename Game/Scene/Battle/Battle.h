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

namespace scene{
namespace battle{

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
	std::shared_ptr<EnemyData> enemy_m;
	DataManager dataManager_m;
	std::shared_ptr<PictureObject> enemyPic_m;

	int enemy_ID_List_m[31];

	// objects
	std::multimap<String, std::shared_ptr<BattleSceneObject>> objects;
	std::multimap<String, std::shared_ptr<BattleSceneButton>> buttons;
	DrawableList drawList_m;

	std::shared_ptr<BattleSceneButton> titleButton;

	std::shared_ptr<TextView> message_m;

	// state
	enum BattleState { win, lose, select };
	BattleState state_m;

	// background
	std::shared_ptr<PictureObject> backPic_m;
};

};

};

