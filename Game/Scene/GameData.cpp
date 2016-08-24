#include "GameData.h"



GameData::GameData()
{}


GameData::~GameData()
{}

void GameData::addEnemy(int id) {
	defeatedEnemyList.push_back(id);
}

void GameData::resetEnemyList() {
	defeatedEnemyList.clear();
}