#include "GameData.h"



GameData::GameData()
{
    time = 0;
}


GameData::~GameData()
{}

void GameData::addEnemy(int id) {
	defeatedEnemyList.push_back(id);
}

void GameData::resetEnemyList() {
	defeatedEnemyList.clear();
}