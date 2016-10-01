#include "GameData.h"



GameData::GameData()
{
    time = 0;
	for(int i = 1; i <= 10; ++i) {
		defeatedEnemyList.push_back(i);
	}
}


GameData::~GameData()
{}

void GameData::addEnemy(int id) {
	defeatedEnemyList.push_back(id);
}

void GameData::resetEnemyList() {
	defeatedEnemyList.clear();
}