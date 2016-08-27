#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "../../Data/DataManager.h"
#include "../../Data/EnemyData.h"
#include "MyDrawableList.h"
#include "EnemyGuide.h"


class GameData;

using Scene = SceneManager<String, GameData>::Scene;

namespace scene {
	namespace enemyGuide {
		class EGDetailType : public EnemyGuide, public Scene
		{
		private:
			static const double NEXT_BUTTON_WIDTH;
			static const double NEXT_BUTTON_HEIGHT;
			static const double PREVIOUS_BUTTON_WIDTH;
			static const double PREVIOUS_BUTTON_HEIGHT;
			static const double LIST_BUTTON_WIDTH;
			static const double LIST_BUTTON_HEIGHT;
			
			static const double TARGET_SCALE ;

			static const Point POS_NEXT_BUTTON;
			static const Point POS_PREVIOUS_BUTTON;
			static const Point POS_LIST_BUTTON;
			static const Point POS_TARGET;
			static const Point POS_TARGET_NAME;
			static const Point POS_TARGET_MESSAGE;
			static const Point POS_COLLECT_ANSWER;
			static const Point POS_DESCRIPTION;


			DataManager dataManager_m;

			EnemyData target_m;

			std::function<void(void)> goToNext_m;
			std::function<void(void)> backToPrevious_m;
			std::function<void(void)> backToList_m;

			std::shared_ptr<RoundRectTextButton> nextButton_m;
			std::shared_ptr<RoundRectTextButton> previousButton_m;
			std::shared_ptr<RoundRectTextButton> backToListButton_m;

			int cursorID_m;

			Font targetName_m;
			Font targetMessage_m;
			Font collectAnswer_m;
			Font description_m;

			MyDrawableList targetGraphics_m;

			void changeTarget();
			void nextTarget(int* address);
			void previousTarget(int* address);
		public:
			void init() override;
			void update() override;
			void draw()const override;
		};
	}
}

