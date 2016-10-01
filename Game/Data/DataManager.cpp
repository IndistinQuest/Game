#include "DataManager.h"

const String DataManager::JSONPath = L"/1101";//L"JSONData / Enemy.json";
const String DataManager::CSVPath = L"CSVData/SaveData.csv";

const int DataManager::KIND_OF_ENEMY = 30;

DataManager::DataManager()
{
	readEnemyData();
	if (!FileSystem::Exists(CSVPath))
	{
		initSaveData();
	}
	readSaveData();
}


DataManager::~DataManager()
{
}

void DataManager::initSaveData()
{
	saveDataWriter_m.open(CSVPath);
	for (int i = 0; i <= 30;++i) {
		saveDataWriter_m.writeRow(i, false);
	}
	saveDataWriter_m.close();
}

int DataManager::getNumOfEnemies()
{
	return static_cast<int>(enemies_m.size());
}

EnemyData const DataManager::getEnemy(int id)
{
	auto findFromID = [id](EnemyData enemy) {return enemy.id_m == id; };
	return *std::find_if(enemies_m.begin(), enemies_m.end(), findFromID);
}

SaveData const DataManager::getSaveData(int id) 
{
	auto findFromID = [id](SaveData obj) {return obj.id_m == id; };
	return *std::find_if(saveData_m.begin(), saveData_m.end(), findFromID);
}

void DataManager::setSaveData(int id, bool defeated)
{
	auto findFromID = [id](SaveData obj) {return obj.id_m == id; };
	(*std::find_if(saveData_m.begin(), saveData_m.end(), findFromID)).isDefeated_m = defeated;
}

void DataManager::readEnemyData()
{
	enemyReader_m.open(JSONPath);
	for (auto& object : enemyReader_m[L"Enemy"].getObject())
	{
		EnemyData enemy;

		enemy.id_m = object.second[L"id"].get<int32>();
		enemy.name_m = object.second[L"name"].get<String>();

		enemy.messages_m.onContact_m = object.second[L"messages"][L"onContact"].get<String>();
		enemy.messages_m.onPlayerWon_m = object.second[L"messages"][L"onPlayerWon"].get<String>();
		enemy.messages_m.onPlayerLost_m = object.second[L"messages"][L"onPlayerLost"].get<String>();

		enemy.collectAnswer_m = object.second[L"collectAnswer"].get<String>();

		for (const auto& weapon : object.second[L"Answers"][L"weapon"].getArray())
		{
			enemy.answers_m.weapon_m.push_back(weapon.get<String>());
		}
		for (const auto& magic : object.second[L"Answers"][L"magic"].getArray())
		{
			enemy.answers_m.magic_m.push_back(magic.get<String>());
		}
		for (const auto& special : object.second[L"Answers"][L"special"].getArray())
		{
			enemy.answers_m.special_m.push_back(special.get<String>());
		}

		enemy.description_m = object.second[L"description"].get<String>();
		enemy.bgid_m = object.second[L"BGID"].get<int>();

		enemies_m.push_back(enemy);
	}
	enemyReader_m.close();
}

void DataManager::readSaveData()
{
	saveDataReader_m.open(CSVPath);
	for (int i = 0; i < saveDataReader_m.rows; ++i)
	{
		SaveData saveData;
		saveData.id_m = saveDataReader_m.get<int>(i, 0);
		saveData.isDefeated_m = saveDataReader_m.get<bool>(i, 1);
		saveData_m.push_back(saveData);
	}
	saveDataReader_m.close();
}

void DataManager::writeSaveData()
{
	saveDataWriter_m.open(CSVPath);
	for (auto data : saveData_m)
	{
		saveDataWriter_m.writeRow(data.id_m, data.isDefeated_m);
	}
	saveDataWriter_m.close();
}

void DataManager::clearSaveDate()
{
	saveDataWriter_m.open(CSVPath);
	for (int i = 1; i <= KIND_OF_ENEMY; ++i)
	{
		saveDataWriter_m.writeRow(i, false);
	}
	saveDataWriter_m.close();
}


