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
enum BattleState { Start, EnemyEntry, Answer, CanNotAnswer, Incorect, Corect, ExitEnemy, AcceptedClick, TimeOver, GameOver,GameClear };

class RoundCounter;
class MessageWindow;
class Timer;

class EnemyIdList;


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
	bool incorect;
	bool canAnswer;
	int	penalty_m;

	//enemy
	std::shared_ptr<EnemyData> enemy_m;				// Enemyデータ
	DataManager dataManager_m;						//
	std::shared_ptr<PictureObject> enemyPic_m;		// Enemy画像

	std::shared_ptr<EnemyIdList> enemyList_m;

	// objects
	std::multimap<String, std::shared_ptr<BattleSceneObject>> objects;
	std::multimap<String, std::shared_ptr<BattleSceneButton>> buttons;
	DrawableList drawList_m;

	std::shared_ptr<BattleSceneButton> nextButton;
	std::shared_ptr<BattleSceneButton> CommantButton_m[9];


	std::shared_ptr<CutIn> cutIn_m;					// カットイン

	Effect effect_m;

	// state	
	BattleState state_m;


	std::shared_ptr<PictureObject> backPic_m;		// 背景画像
	
	std::shared_ptr<RoundCounter> roundCounter_m;	// 戦闘数	
	std::shared_ptr<MessageWindow> message_m;		// メッセージ	
	std::shared_ptr<Timer> timer_m;					// タイマー
};

};

};

