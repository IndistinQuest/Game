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
class CutIn;
enum BattleState { Start, EnemyEntry, Answer, CanNotAnswer, Incorect, Corect, ExitEnemy, AcceptedClick, TimeOver, GameOver };

class Battle : public SceneManager<String, GameData>::Scene {
public:
	Battle();
	~Battle();
	void init()override;
	void update()override;
	void draw()const override;

private:
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, String  name, int layer);
	void Battle::nextScene(String sceneName);
	void Battle::newEnemy();	

private:
	int round_m;
	int time_m;

	bool incorect;
	bool canAnswer;
	int	penalty_m;

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
	std::shared_ptr<BattleSceneButton> CommantButton_m[9];

	std::shared_ptr<TextView> message_m;

	std::shared_ptr<CutIn> cutIn_m;

	Effect effect_m;

	// state
	
	BattleState state_m;

	// background
	std::shared_ptr<PictureObject> backPic_m;
};

};

};

