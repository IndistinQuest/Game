#pragma once
#include <Siv3D.hpp>
class EnemyData
{
public:
	int id_m;
	String name_m;
	class Messages
	{
	public:
		String onContact_m;
		String onPlayerWon_m;
		String onPlayerLost_m;
	};
	Messages messages_m;
	String collectAnswer_m;
	class Answers
	{
	public:
		Array<String> weapon_m;
		Array<String> magic_m;
		Array<String> special_m;
	};
	Answers answers_m;
	String description_m;
	int bgid_m;
public:
	EnemyData();
	~EnemyData();
};

