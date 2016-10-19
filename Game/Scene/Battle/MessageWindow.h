#pragma once
#include<Siv3D.hpp>
#include"WindowAndText.h"
#include"EnemyManager.h"
#include"../../TextView/TextView.h"

namespace scene {
	namespace battle {
		//メッセージ
		class MessageWindow : public WindowAndText, public TextView {
		private:
			std::shared_ptr<EnemyManager> enemyManager_m;
			bool incorect_m;			
			const String LOSE_MESSAGE = L"にやられた！";
			const String START_MESSAGE = L"準備はいいですか?\nStartを押すとゲームが始まります!";
		public:
			MessageWindow(Point center, String textureAssetName, Color c = Palette::Black);
			void update()override;
			void draw()const override;
			void setEnemyManager(std::shared_ptr<EnemyManager> e);
		};
	}
}