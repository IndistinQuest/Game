#pragma once
#include <vector>
class GameData
{
public:
    GameData();
    ~GameData();
	std::vector<int> defeatedEnemyList;
	void addEnemy(int id);
	void resetEnemyList();
};

