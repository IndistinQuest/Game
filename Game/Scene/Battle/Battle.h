#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"..\GameData.h"
#include"..\..\Drawable\DrawableList.h"

namespace scene{
namespace battle{

class BattleSceneObject;

class Battle : public SceneManager<String, GameData>::Scene {
public:
	Battle();
	~Battle();
	void init()override;
	void update()override;
	void draw()const override;

private:
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj);
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer);
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer, int order);

private:
	std::multimap<int,std::shared_ptr<BattleSceneObject>> objects;
	DrawableList drawList_m;
};

};
};