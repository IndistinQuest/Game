#pragma once
#include "BattleSceneObject.h"
#include"../GameData.h"
#include"../../Data/EnemyData.h"
#include"../../Data/DataManager.h"
#include"PictureObject.h"
#include"CutIn.h"
#include"RoundCounter.h"

namespace scene {
	namespace battle {

		// エネミーマネージャ
		class EnemyManager : public BattleSceneObject {
		private:
			std::shared_ptr<EnemyData> enemy_m;				// Enemyデータ
			DataManager dataManager_m;						// データマネージャ
			int enemyIdList_m[31];							// 登場順リスト
			std::shared_ptr<GameData> data_m;				// ゲームデータ

			std::shared_ptr<PictureObject> enemyPic_m;		// Enemy画像
			std::shared_ptr<CutIn> cutIn_m;					// カットイン
			std::shared_ptr<PictureObject> backPic_m;		// 背景画像
			std::shared_ptr<RoundCounter> round_m;			// 戦闘数
		public:
			EnemyManager();
			~EnemyManager();
			using pic = std::shared_ptr<PictureObject>;
			void setObjects(pic enemy, pic background, std::shared_ptr<CutIn> cutIn);
			void update()override;
			void draw()const override;
			std::shared_ptr<EnemyData> getEnemy();
			int getId(int round);
			void setRoundCounter(std::shared_ptr<RoundCounter> r);
			void setGameData(std::shared_ptr<GameData> data);
			void newEnemy();
			void writeGameDataAndSaveData(std::shared_ptr<GameData> data);
		private:
			void initIdList();
			void montagePhantom(int round);
			void carillon();
		};
	}
}