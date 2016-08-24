#include"Battle.h"
#include"..\..\Drawable\Drawable.h"
#include"..\..\Button\BasicButton.h"
#include"../../Button/ButtonManager.h"

#include"../../Data/DataManager.h"

using namespace std;
using namespace scene;
using namespace battle;

namespace scene {
namespace battle {

// 値を設定
namespace BattleSceneNums {

	// 制限時間の初期値
	const int timeLimit = 1000;

	// 正解した時の制限時間の増加量
	const int timeRecovery = 300;

	// Enemy画像の拡大率
	const double scale = 0.7;

	// Enemyのフェードイン/アウトの早さ
	const double fadeIn = 10;
	const double fadeOut = 5;

	// 敗北時のEnemyの最大拡大率
	const double maxScale = 2.0;

	// 背景画像の名前
	const String backPicName  = L"title_graphic.JPG";
}

//回答
enum Answers { correct, incorrect, not };
namespace AnswerManager {

	static String corectAnswer;
	static Answers playersAnswer;
	static bool isAnswered;

	void init() {
		isAnswered = false;
	}
	static void setCorectAnswer(String corect){
		corectAnswer = corect;
		isAnswered = false;
	}
	static void answer(String ans) {
		if (ans == corectAnswer) { playersAnswer = Answers::correct; }
		else { playersAnswer = Answers::incorrect; }
		isAnswered = true;
	}
	static Answers checkAnswer() {
		if (isAnswered == false) { playersAnswer = Answers::not; }
		return playersAnswer;
	}
};

// 基底クラス
class BattleSceneObject : public Drawable
{
public:
	virtual void update() = 0;
	virtual void setText(String text) = 0;
};

//ウィンドウ
class WindowAndText	: public BattleSceneObject
{
private:
	const Size size;
	const Point pos;
	const Point center;
	const int r = 10;
	const Color color = Palette::Blue;
	const int Alpha = 120;
protected:
	String str_m;
public:
	WindowAndText(Point pos, Size size, int r = 0, Color color = Palette::Blue)
		:pos(pos), size(size), r(r), color(color), center(pos + size / 2)
	{
		if (!FontAsset::IsRegistered(L"BattleSceneFont")) {
			FontAsset::Register(L"BattleSceneFont", 20, Typeface::Black);
		}
	};
	void update()override {
		//Println(L"TextWindow->OK!");
	};
	void setText(String text)override {
		str_m = text;
	}
	void draw()const override {
		RoundRect(pos, size, r).draw(Color(color).setAlpha(Alpha)).drawFrame(0.3, 0.0, Palette::Black);
		FontAsset(L"BattleSceneFont").drawCenter(str_m, center);
	}
};

//ボタン
class BattleSceneButton : public BasicButton , public BattleSceneObject{
private:
	const Size size;
	const Point pos;
	const Point center;
	const int r = 5;
	const Color color = Palette::Blue;
	const int Alpha = 120;

	String text_m;
public:
	BattleSceneButton(Point pos,Size size)
		:BasicButton(Shape(RoundRect(pos, size,r)))//,text_m(text)
		, size(size), pos(pos), center(pos + size / 2) {
		if (!FontAsset::IsRegistered(L"CommandFont")) {
			FontAsset::Register(L"CommandFont", 20, Typeface::Black);
		}
	};
	void draw() const
	{
		switch (getState()) {
		case State::LEFT:		
		case State::MOUSE_OVER:		
		case State::PRESSED:
		case State::RELEASED:
			RoundRect(pos, size, r).draw(Color(color).setAlpha(Alpha)).drawFrame(0.3, 0.0, Palette::Black);
			break;
		default:
			break;
		}
		FontAsset(L"CommandFont").drawCenter(text_m, center);
	}
	void setText(String text)override {
		text_m = text;
	}
	void onClicked()override {
		AnswerManager::answer(text_m);
	}
	void update()override {
		//Println(L"Button is Update");
	}
};

//画像
class PictureObject : public BattleSceneObject{
private:
	FilePath path;
	Texture texture;
	Point pos;
	double scale;
	double defaultScale;
	double alpha;
	bool isFadeOut;
	bool isFadeIn;
	bool isExpansion;
	double rad;
public:
	PictureObject(String picName,double scale,Point pos):pos(pos),defaultScale(scale) {
		setText(picName);
		init();
	}
	void update()override {
		if (isFadeIn && alpha < 255) {
			alpha += BattleSceneNums::fadeIn;			
			if (alpha > 255) { alpha = 255; }

			scale += BattleSceneNums::fadeIn/255;
			if (scale > defaultScale) { scale = defaultScale; }
		}
		if (isFadeOut && alpha > 0) { 
			alpha -= BattleSceneNums::fadeOut;
			if (alpha < 0) { alpha = 0; }

			scale -= BattleSceneNums::fadeOut/255;
			if (scale < 0) { scale = 0; }

			rad += 0.1;
		}
		if (isExpansion && scale <= BattleSceneNums::maxScale) {
			scale += 0.1;
			if (scale > BattleSceneNums::maxScale) { scale = BattleSceneNums::maxScale; }
		}
	}
	// 新しい画像に変える
	// String text 画像の名前
	void setText(String text)override {
		path = L"Asset/" + text;
		texture = Texture(path);
		setFadeIn();
	}
	void draw()const override {
		Point drawPos = pos + Point(Math::Cos(System::FrameCount()), 0);
		texture.scale(scale).rotate(rad).drawAt(drawPos,Color(Palette::White).setAlpha(alpha));
	}
	void init() {
		scale = defaultScale;
		alpha = 255;
		isFadeOut = false;
		isFadeIn = false;
		isExpansion = false;
		rad = 0;
	}
	void setFadeOut() {
		isFadeOut = true;
		isFadeIn = false;
	}
	void setFadeIn() {
		init();
		isFadeIn = true;
		isFadeOut = false;
		alpha = 0;
		scale = 0.0;
	}
	bool isDraw() {
		if (alpha > 0) { return true; }
		else { return false; }
	}
	void setExpansion(){
		isExpansion = true;
	}
};

}
}

/***********************************************************************************************************************/

Battle::Battle() {};

Battle::~Battle(){};

void Battle::init(){

	ButtonManager::clearAll();
	ButtonManager::update();

	m_data->resetEnemyList();

	const int tx = 5;
	const int ty = 5;

	const int roundWidth = 190;
	const int timeWidth = 190;
	const int mesWidth = Window::Width() - (tx * 4) - roundWidth - timeWidth;

	// Window
	const int bWindowHeight = 130;

	// round
	round_m = 1;
	auto r = WindowAndText({ tx, ty }, { roundWidth,bWindowHeight }, 10);
	r.setText(L"1戦目");
	addObject(make_shared<WindowAndText>(r), L"RoundWindow", 10);	
		
	// message
	message_m = make_shared<TextView>(L"testMessage", Point(roundWidth + tx*4, ty*2), mesWidth-tx, 3, Font(20, Typeface::Black));
	drawList_m.add(message_m,11);

	auto m = WindowAndText({ tx * 2 + roundWidth ,ty }, { mesWidth,bWindowHeight }, 10);
	addObject(make_shared<WindowAndText>(m), L"messageWindow", 10);

	// timer
	time_m = BattleSceneNums::timeLimit;
	auto t = WindowAndText({ tx * 3 + roundWidth + mesWidth ,ty }, { timeWidth,bWindowHeight }, 10);
	t.setText(Format(time_m));
	addObject(make_shared<WindowAndText>(t), L"timeWindow", 10);

	// Button
	const int width = (Window::Width() - tx * 4) / 3;
	const int height = 60;

	const Array<String> buttonName = { L"weapon", L"magic",L"special" };
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 3; j++) {
			auto b = std::make_shared<BattleSceneButton>(BattleSceneButton({ Window::Width() / 2 -width/2  + (width+tx) * (i - 1), Window::Height() - (height+ty) * (3-j) },Size(width,height)));
			b->setText(Format(Window::Width() / 2 + 500 * (i - 1)));
			ButtonManager::add(b);
			addObject(b, Format(buttonName[i],j), 10);
		}
	}

	// AnswerManager
	AnswerManager::init();

	//back
	auto back = PictureObject(BattleSceneNums::backPicName,1.0,Window::Center());
	addObject(make_shared<PictureObject>(back), L"background", 1);	

	//enemyData
	auto enemy = make_shared<PictureObject>(L"null",BattleSceneNums::scale,Point(Window::Width()/2,330));
	addObject(enemy, L"enemy",5);
	enemyPic_m = enemy;
	newEnemy();

	//state
	state_m = BattleState::select;	
};

// 要修正項目あり
void Battle::update(){
	ClearPrint();
	for_each(objects.begin(), objects.end(), [](auto pare) {pare.second->update(); });
	message_m->update();
	
	switch (state_m)
	{
	case BattleState::select:
		// 回答
		{
			auto ans = AnswerManager::checkAnswer();
			//if (ans == Answers::not) { Println(L"未回答"); }
			if (ans == Answers::correct) {
				state_m = BattleState::win;
				message_m->setNewText(enemy_m.messages_m.onPlayerWon_m);
				enemyPic_m->setFadeOut();
				time_m += BattleSceneNums::timeRecovery;

				dataManager_m.setSaveData(enemy_m.id_m, true);
				m_data->addEnemy(enemy_m.id_m);
				
			}
			else if (ans == Answers::incorrect) {
				// 不正解の時は何もしない
				/*state_m = BattleState::lose;
				message_m->setNewText(enemy_m.messages_m.onPlayerLost_m);
				enemyPic_m->setExpansion();*/
			}
		}
		// タイマー
		{
			time_m--;
			objects.find(L"timeWindow")->second->setText(Format(time_m));
			if (time_m <= 0) {
				state_m = BattleState::lose;
				message_m->setNewText(enemy_m.messages_m.onPlayerLost_m);
				enemyPic_m->setExpansion();
			}
		}
		break;
	case BattleState::win:
		//Println(L"正解");
		if (message_m->isPlotAll() && !enemyPic_m->isDraw()) {
			newEnemy();
			state_m = BattleState::select;
			round_m++;
			objects.find(L"RoundWindow")->second->setText(Format(round_m,L"戦目"));
		}
		break;
	case BattleState::lose:
		//Println(L"不正解");
		if (message_m->isPlotAll()) {
			dataManager_m.writeSaveData();
			changeScene(L"GameOver");				///書き換える
		}		
		break;
	}	
};

void Battle::draw()const{
	drawList_m.drawAll();
};

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, String  name, int layer) {
	objects.insert(std::make_pair(name, obj));
	drawList_m.add(obj, layer);
}

// 要修正項目あり
void Battle::newEnemy() {
	/*int rand;
	do{
		rand = Random(1, dataManager_m.getNumOfEnemies() );
		enemy_m = dataManager_m.getEnemy(rand);
	} while (enemy_m.id_m == rand && dataManager_m.getNumOfEnemies() != 1);*/

	int rand = Random(1,20);				//// 要修正
	enemy_m = dataManager_m.getEnemy(0);	//   要修正
	
	AnswerManager::setCorectAnswer(enemy_m.collectAnswer_m);	
	objects.find(L"enemy")->second->setText(Format(L"EnemyGraphics/", rand, L".png"));

	message_m->setNewText(enemy_m.name_m + L"があらわれた \n" + enemy_m.messages_m.onContact_m);		// 修正可能性あり

	const Array<String> buttonName = { L"weapon", L"magic",L"special" };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {			
			auto b = objects.find(Format(buttonName[i], j))->second;
			switch (i)
			{
			case 0:
				b->setText(enemy_m.answers_m.weapon_m[j]);
				break;
			case 1:
				b->setText(enemy_m.answers_m.magic_m[j]);
				break;
			case 2:
				b->setText(enemy_m.answers_m.special_m[j]);	
				break;
			default:				
				break;
			}
		}
	}

}
