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

		// �G�l�~�[�}�l�[�W��
		class EnemyManager : public BattleSceneObject {
		private:
			std::shared_ptr<EnemyData> enemy_m;				// Enemy�f�[�^
			DataManager dataManager_m;						// �f�[�^�}�l�[�W��
			int enemyIdList_m[31];							// �o�ꏇ���X�g
			std::shared_ptr<GameData> data_m;				// �Q�[���f�[�^

			std::shared_ptr<PictureObject> enemyPic_m;		// Enemy�摜
			std::shared_ptr<CutIn> cutIn_m;					// �J�b�g�C��
			std::shared_ptr<PictureObject> backPic_m;		// �w�i�摜
			std::shared_ptr<RoundCounter> round_m;			// �퓬��
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