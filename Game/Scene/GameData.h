#pragma once
#include <vector>
class GameData
{
public:
	std::vector<int> defeatedEnemyList;
    GameData();
    ~GameData();
	void addEnemy(int id);
    void resetEnemyList();
	int time;
};

