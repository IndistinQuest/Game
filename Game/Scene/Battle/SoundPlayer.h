#pragma once
#include"BattleSceneObject.h"
namespace scene {
	namespace battle {
		// �T�E���h
		class SoundPlayer : public BattleSceneObject {
			String bgmName_m;
		public:
			SoundPlayer();
			~SoundPlayer();
			void update()override;
			void draw()const override;
		};
	}
}