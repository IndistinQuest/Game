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
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj);								//�`�悵�Ȃ��I�u�W�F�N�g�̒ǉ�
	void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer, int order = 4);	//�`�惌�C���[�Ə��������w�肵�ăI�u�W�F�N�g��ǉ�

private:
	std::multimap<int,std::shared_ptr<BattleSceneObject>> objects;
	DrawableList drawList_m;
};

};
};