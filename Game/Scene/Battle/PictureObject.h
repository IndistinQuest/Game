#pragma once
#include"BattleSceneObject.h"
namespace scene {
	namespace battle {
		//画像
		class PictureObject : public BattleSceneObject {
		private:
			String aseetName;
			Point pos;
			double scale;
			double defaultScale;
			double alpha;
			bool isFadeOut;
			bool isFadeIn;
			bool isExpansion;
			double rad;
			bool isRoolAndSmall;
			bool isBigger;
			Size picSize;
			const double SCALE = 1.0; // Enemy画像の拡大率
			// Enemyのフェードイン/アウトの早さ
			const double FADE_IN = 15;
			const double FADE_OUT = 5;
			const double MAX_SCALE = 5;// 敗北時のEnemyの最大拡大率			
		public:
			PictureObject(String assetName, double scale, Point pos);
			void update()override;
			void changeTexture(String assetname);
			void draw()const override;
			void init();
			void setFadeOut();
			void setRoolAndSmall();
			void setBigger();
			void setFadeIn();
			bool isDraw();
			void setExpansion();
		};

	}
}