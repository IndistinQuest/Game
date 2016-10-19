#pragma once
#include<Siv3D.hpp>
namespace scene {
	namespace battle {
		// ���
		enum class BattleState { Start, EnemyEntry, Answer, CanNotAnswer, Incorect, Corect, ExitEnemy, TimeOver, GameOver, BackToTitle, GoToResult, CheckGameClear };

		// �X�e�[�g�}�l�[�W��
		class StateManager {
		private:
			static bool isGoTitle;
			static bool isGameClear;
			static bool isTimeOver;
			static bool isImprove;
			static BattleState curentState_m;
		public:
			static void init();
			static void update();
			static BattleState getState();
			static void setNextState(BattleState next);
			static void setBackToTitle();
			static void setTimeOver();
			static void setGameClear();
			static void goToNext();
		};
	}
}