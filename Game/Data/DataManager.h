#pragma once
#include <algorithm>
#include <Siv3D.hpp>
#include "EnemyData.h"
#include "SaveData.h"

class DataManager
{
public:
	JSONReader enemyReader_m;
	Array<EnemyData> enemies_m;

public:
	DataManager();
	~DataManager();

	int getNumOfEnemies();
	EnemyData getEnemy(int id);
	SaveData getSaveData(int id);
	void setSaveData(int id, bool defeated);

	void read();
	void writeSaveData();
};

