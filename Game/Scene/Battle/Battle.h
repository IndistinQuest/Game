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
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj);								//描画しないオブジェクトの追加
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer, int order = 4);	//描画レイヤーと処理順を指定してオブジェクトを追加

private:
	std::multimap<int,std::shared_ptr<BattleSceneObject>> objects;
	DrawableList drawList_m;
};

};
};