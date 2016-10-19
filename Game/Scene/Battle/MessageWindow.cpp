#include"MessageWindow.h"
#include"StateManager.h"
using namespace scene::battle;

MessageWindow::MessageWindow(Point center, String textureAssetName, Color c)
	: WindowAndText(center, textureAssetName, c)
	, TextView(L"", Point(210, center.y - 60), 850, 3, Font(20), 1, Palette::Black) {
	setNewText(START_MESSAGE);
	incorect_m = false;
}
void MessageWindow::update(){

	switch (StateManager::getState())
	{
	case BattleState::Answer:
		if (incorect_m && isAllPoltAndOverTime()) {
			setNewText(enemyManager_m->getEnemy()->messages_m.onContact_m);
			incorect_m = false;
		}
		break;
	case BattleState::EnemyEntry:
		setNewText(enemyManager_m->getEnemy()->messages_m.onContact_m);
		incorect_m = false;
		break;
	case BattleState::TimeOver:
		setNewText(enemyManager_m->getEnemy()->name_m + LOSE_MESSAGE);
		break;
	case BattleState::Corect:
		setNewText(enemyManager_m->getEnemy()->messages_m.onPlayerWon_m);
		break;
	case BattleState::Incorect:
		setNewText(enemyManager_m->getEnemy()->messages_m.onPlayerLost_m);
		incorect_m = true;
		break;
	default:
		break;
	}

	TextView::update();
}
void MessageWindow::draw()const{
	WindowAndText::draw();
	TextView::draw();
}
void MessageWindow::setEnemyManager(std::shared_ptr<EnemyManager> e) {
	enemyManager_m = e;
}
