#include"AnswerManager.h"
using namespace scene::battle;
void AnswerManager::init() {
	isAnswered = false;
};
void AnswerManager::setCorectAnswer(String corect) {
	corectAnswer = corect;
	isAnswered = false;
};
void AnswerManager::answer(String ans) {
	playersAnswer = (ans == corectAnswer) ? Answers::correct : Answers::incorrect;
	isAnswered = true;
};
Answers AnswerManager::checkAnswer() {
	if (isAnswered == false) { playersAnswer = Answers::not; }
	return playersAnswer;
};		
String AnswerManager::corectAnswer = L"";
Answers AnswerManager::playersAnswer = Answers::not;
bool AnswerManager::isAnswered = false;
