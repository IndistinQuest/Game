#pragma once
#include"AnswerButton.h"
#include"BattleSceneObject.h"
#include"EnemyManager.h"
#include"StateManager.h"
namespace scene {
	namespace battle {
		// 回答のボタン郡
		class AnswerButtons : public BattleSceneObject 
		{
		private:
			std::shared_ptr<EnemyManager> enemyManager_m;
			std::shared_ptr<AnswerButton> buttons_m[9];
			int penalty_m;			
			const int PENALTY_TIME = 120;// 間違えた時ボタンが押せなくなる時間
		public:
			AnswerButtons();
			void update()override;
			void draw()const override;
			void setAnswers();
			void setEnemyManager(std::shared_ptr<EnemyManager> e);
		};
	}
}