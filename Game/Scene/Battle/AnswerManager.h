#pragma once
#include<Siv3D.hpp>

namespace scene {
	namespace battle {	
		// 回答状態
		enum Answers { correct, incorrect, not };
		// アンサーマネージャ
		class AnswerManager {
		private:
			static String corectAnswer;
			static Answers playersAnswer;
			static bool isAnswered;
		public:
			static void init();
			static void setCorectAnswer(String corect);
			static void answer(String ans);
			static Answers checkAnswer();
		};
	}
}