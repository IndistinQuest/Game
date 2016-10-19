#pragma once
#include<Siv3D.hpp>
#include"WindowAndText.h"
#include"../GameData.h"
namespace scene {
	namespace battle {
		// タイマー
		class Timer : public WindowAndText {
		private:
			int time_m;
			std::shared_ptr<GameData> data_m;
			Stopwatch stopWatch_m;			
			const int TIME_LIMIT = 30000;// 制限時間の初期値			
			const int TIME_RECOVERY = 7000;// 正解した時の制限時間の増加量
		public:
			Timer(Point center, String textureAssetName, Color c = Palette::Black);
			~Timer();
			void update() override;
			void recovery();
			void setGameData(std::shared_ptr<GameData> data);
			void timeShow();
			int getCurentTime();
		};
	}
}