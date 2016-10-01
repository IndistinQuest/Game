#pragma once
#include <algorithm>
#include <Siv3D.hpp>
#include "EnemyData.h"
#include "SaveData.h"

class DataManager
{
private:
	static const String JSONPath;
	static const String CSVPath;
	static const int KIND_OF_ENEMY;
private:
	void initSaveData();
public:
	JSONReader enemyReader_m;
	CSVReader saveDataReader_m;
	CSVWriter saveDataWriter_m;
private:
	Array<EnemyData> enemies_m;
	Array<SaveData> saveData_m;
public:
	DataManager();
	~DataManager();

	int getNumOfEnemies();
	EnemyData const getEnemy(int id);
	SaveData const getSaveData(int id);
	void setSaveData(int id, bool defeated);

private:
	void readEnemyData();
	void readSaveData();
public:
	void writeSaveData();
	void clearSaveDate();
};

