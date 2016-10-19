#include"RoundCounter.h"
#include"StateManager.h"
using namespace scene::battle;

RoundCounter::RoundCounter(Point center, String textureAssetName, Color c)
	:WindowAndText(center, textureAssetName, c) {
	round_m = -1;
	next();
}
void RoundCounter::next() {
	round_m++;
	setText(Format(round_m, L"í–Ú"));
}
void RoundCounter::update(){	
	switch (StateManager::getState()) {
	case BattleState::EnemyEntry:
		next();
		break;
	case BattleState::CheckGameClear:
		if (isGameClear()) {
			round_m++;
			StateManager::setGameClear();
		}
		break;
	default:
		break;
	}
}
bool RoundCounter::isGameClear()const {
	return round_m >= 30;
}
int RoundCounter::getRound()const {
	return round_m;
}
