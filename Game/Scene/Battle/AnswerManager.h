#pragma once
#include<Siv3D.hpp>

namespace scene {
namespace battle {

enum Answers { correct, incorrect, not };
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