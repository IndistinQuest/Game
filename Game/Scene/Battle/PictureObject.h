#pragma once
#include"BattleSceneObject.h"
namespace scene {
	namespace battle {
		//�摜
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
			const double SCALE = 1.0; // Enemy�摜�̊g�嗦
			// Enemy�̃t�F�[�h�C��/�A�E�g�̑���
			const double FADE_IN = 15;
			const double FADE_OUT = 5;
			const double MAX_SCALE = 5;// �s�k����Enemy�̍ő�g�嗦			
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