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
	const int timeRecovery = 200;

	// Enemy画像の拡大率
	const double scale = 0.4;

	// Enemyのフェードイン/アウトの早さ
	const double fadeIn = 10;
	const double fadeOut = 3;

	// 敗北時のEnemyの最大拡大率
	const double maxScale = 2.0;

	// 背景画像の名前
	const String backPicName = L"background.png";

	// 次のシーン
	const String nextScene = L"Result";//L"GameOver";

	// 敗北時のメッセージ
	const String loseMessage = L"にやられた！";

	// メッセージ表示速度
	const int mesSpeed = 3;

	// ボタンのファイル名
	const String buttonName = L"window_graphic.png";

	// 戦闘数のウィンドウのファイル名
	const String rWindowName = L"small_message_graphic.png";

	// メッセージウィンドウのファイル名
	const String mWindowName = L"message_graphic.png";

	// 制限時間のウィンドウのファイル名
	const String tWindowName = L"small_message_graphic.png";

	// 正解時のSE
	const String seCorect = L"crrect_answer3.mp3";

	// 不正解時のSE
	const String seInCorect = L"powerdown07.mp3";

	// 敗北時SE
	const String seLose = L"damage7.mp3";

	// BGM
	const String bgm = L"bgm_maoudamashii_neorock49.ogg";
}

//回答
enum Answers { correct, incorrect, not };
namespace AnswerManager {

	static String corectAnswer = L"";
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
	/*const int r = 10;
	const Color color = Palette::Blue;
	const int Alpha = 120;*/
	const Texture texture_m;
	const Color strColor_m;
protected:
	String str_m;
public:
	WindowAndText(Point pos, Size size,FilePath path,Color c = Palette::Black)
		:pos(pos), size(size),center(pos + size / 2),texture_m(path),
		strColor_m(c)
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
		//RoundRect(pos, size, r).draw(Color(color).setAlpha(Alpha)).drawFrame(0.3, 0.0, Palette::Black);
		texture_m.drawAt(center);
		FontAsset(L"BattleSceneFont").drawCenter(str_m, center,strColor_m);
	}
};

//ボタン
class BattleSceneButton : public BasicButton , public BattleSceneObject{
private:
	const Size size;
	const Size def = {2,2};
	const Point pos;
	const Point center;
	const int r = 5;
	const int Alpha = 120;
	String text_m;
	const Texture texture_m;
	Color color_m;	//文字色
public:
	BattleSceneButton(Point pos,Size size,String filepath,Color c = Palette::White)
		:BasicButton(Shape(RoundRect(pos, size,r)))//,text_m(text)
		, size(size), pos(pos), center(pos + size / 2)
		,texture_m(filepath),color_m(c)
	{
		if (!FontAsset::IsRegistered(L"CommandFont")) {
			FontAsset::Register(L"CommandFont", 20, Typeface::Black);
		}
	};
	void draw() const
	{
		Point bPos = center;
		double mag = 1.0;
		switch (getState()) {
		case State::LEFT:
			break;
		case State::MOUSE_OVER:
			bPos.moveBy({0,-2});
			mag = 1.01;
			break;
		case State::PRESSED:
		case State::RELEASED:
		default:
			//RoundRect(pos, size, r).draw(Color(Palette::Blue).setAlpha(Alpha)).drawFrame(0.3, 0.0, Palette::Black);
			break;
		}
		texture_m.scale(mag).drawAt(bPos);
		FontAsset(L"CommandFont").drawCenter(text_m, bPos,color_m);
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
	void setStrColor(Color c) {
		color_m = c;
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
	bool isRoolAndSmall;
	bool isBigger;
	Size picSize;
public:
	PictureObject(String picName,double scale,Point pos):pos(pos),defaultScale(scale){
		setText(picName);
		init();
	}
	void update()override {
		if (isFadeIn && alpha < 255) {
			alpha += BattleSceneNums::fadeIn;			
			if (alpha > 255) { alpha = 255; }

			if (isBigger) {
				scale += BattleSceneNums::fadeIn / 255;
				if (scale > defaultScale) { scale = defaultScale; }
			}
		}
		if (isFadeOut && alpha > 0) { 
			alpha -= BattleSceneNums::fadeOut;
			if (alpha < 0) { alpha = 0; }

			if (isRoolAndSmall) {
				scale -= BattleSceneNums::fadeOut / 255;
				if (scale < 0) { scale = 0; }

				rad += 0.1;
			}			
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
		texture.scale(scale).rotate(rad).drawAt(drawPos, Color(Palette::White).setAlpha(static_cast<int>(alpha)));
	}
	void init() {
		scale = defaultScale;
		alpha = 255;
		isFadeOut = false;
		isFadeIn = false;
		isExpansion = false;
		rad = 0;
		isRoolAndSmall = false;
		isBigger = false;
	}
	void setFadeOut() {
		isFadeOut = true;
		isFadeIn = false;
	}
	void setRoolAndSmall() {
		isRoolAndSmall = true;
	}
	void setBigger() {
		scale = 0.0;
		isBigger = true;
	}
	void setFadeIn() {
		init();
		isFadeIn = true;
		isFadeOut = false;
		alpha = 0;
	}
	bool isDraw() {
		if (alpha > 0) { return true; }
		else { return false; }
	}
	void setExpansion(){
		isExpansion = true;
	}
};

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

}
}

/***********************************************************************************************************************/

Battle::Battle() {};

Battle::~Battle(){};

void Battle::init(){

	Graphics::SetBackground(Palette::Lightslategray);

	ButtonManager::clearAll();
	ButtonManager::update();

	m_data->resetEnemyList();
	m_data->time = 0;

	// font
	if (!FontAsset::IsRegistered(L"CommandFont")) {
		FontAsset::Register(L"CommandFont", 20);
	}
	if (!FontAsset::IsRegistered(L"BattleSceneFont")) {
		FontAsset::Register(L"BattleSceneFont", 20);
	}

	const int tx = 5;
	const int ty = 5;

	const int roundWidth = 190;
	const int timeWidth = 190;
	const int mesWidth = Window::Width() - (tx * 4) - roundWidth - timeWidth;

	// Window
	const int bWindowHeight = 130;

	// round
	round_m = 1;
	auto r = WindowAndText({ tx, ty*3 }, { roundWidth,bWindowHeight },assetPath + BattleSceneNums::rWindowName);
	r.setText(L"1戦目");
	addObject(make_shared<WindowAndText>(r), L"RoundWindow", 10);	
	
	// message
	message_m = make_shared<TextView>(L"testMessage", Point(roundWidth + tx*4, ty*4), mesWidth-tx, 3, Font(20),BattleSceneNums::mesSpeed,Palette::Black);
	drawList_m.add(message_m,11);

	auto m = WindowAndText({ tx * 2 + roundWidth ,ty*3 }, { mesWidth,bWindowHeight }, assetPath + BattleSceneNums::mWindowName);
	addObject(make_shared<WindowAndText>(m), L"messageWindow", 10);

	// timer
	time_m = BattleSceneNums::timeLimit;
	maxTime_m = BattleSceneNums::timeLimit;
	auto t = WindowAndText({ tx * 3 + roundWidth + mesWidth ,ty*3 }, { timeWidth,bWindowHeight },assetPath + BattleSceneNums::tWindowName);
	t.setText(Format(time_m));
	addObject(make_shared<WindowAndText>(t), L"timeWindow", 10);

	// Button
	const int width = (Window::Width() - tx * 4) / 3;
	const int height = 60;

	const Array<String> buttonName = { L"weapon", L"magic",L"special" };
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 3; j++) {
			auto b = std::make_shared<BattleSceneButton>(BattleSceneButton({ Window::Width() / 2 -width/2  + (width+tx) * (i - 1), Window::Height() - (height+ty) * (3-j) },Size(width,height),assetPath + BattleSceneNums::buttonName));
			b->setText(Format(Window::Width() / 2 + 500 * (i - 1)));
			b->setStrColor(Palette::Black);
			ButtonManager::add(b);
			addObject(b, Format(buttonName[i],j), 10);
		}
	}

	// AnswerManager
	AnswerManager::init();

	//back
	auto back = make_shared<PictureObject>(BattleSceneNums::backPicName,1.0,Window::Center());
	backPic_m = back;
	addObject(back, L"background", 1);	

	// Enemy ID List
	// 16 22 29 が特殊
	for (int i = 1; i <= 30; i++)enemy_ID_List_m[i]=i;
	swap(enemy_ID_List_m[16], enemy_ID_List_m[27]);
	swap(enemy_ID_List_m[22], enemy_ID_List_m[28]);
	for (int i = 1; i <= 26; i++) {
		swap(enemy_ID_List_m[i], enemy_ID_List_m[Random(1, 26)]);
	}
	swap(enemy_ID_List_m[27], enemy_ID_List_m[Random(15, 29)]);
	swap(enemy_ID_List_m[28], enemy_ID_List_m[Random(15, 29)]);
	swap(enemy_ID_List_m[29], enemy_ID_List_m[Random(15, 29)]);

	//enemyData
	auto enemy = make_shared<PictureObject>(L"null", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemy, L"enemy",5);
	enemyPic_m = enemy;
	newEnemy();

	//state
	state_m = BattleState::select;	

	// sound
	SoundAsset::Register(L"battle_corect", assetPath + BattleSceneNums::seCorect);
	SoundAsset::Register(L"battle_incorect", assetPath + BattleSceneNums::seInCorect);
	SoundAsset::Register(L"battle_bgm", assetPath + BattleSceneNums::bgm);
	SoundAsset::Register(L"bettle_GameOver", assetPath + BattleSceneNums::seLose);

	SoundAsset(L"battle_bgm").setPosSec(1.0s);
	SoundAsset(L"battle_bgm").setLoop(true);
	SoundAsset(L"battle_bgm").play();

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
				message_m->setNewText(enemy_m->messages_m.onPlayerWon_m);
				enemyPic_m->setFadeOut();
				enemyPic_m->setRoolAndSmall();
				backPic_m->setFadeOut();

				time_m += BattleSceneNums::timeRecovery;
				if (time_m > maxTime_m) { time_m = maxTime_m; }
				maxTime_m = time_m;

				dataManager_m.setSaveData(enemy_m->id_m, true);
				m_data->addEnemy(enemy_m->id_m);
				
				SoundAsset(L"battle_corect").play();
			}
			else if (ans == Answers::incorrect) {
				message_m->setNewText(enemy_m->messages_m.onPlayerLost_m);
				AnswerManager::init();
				SoundAsset(L"battle_incorect").playMulti();
			}
		}
		// タイマー
		{
			time_m--;
			objects.find(L"timeWindow")->second->setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m%60, { 2, L'0' })));
			if (time_m <= 0) {
				state_m = BattleState::lose;
				message_m->setNewText(enemy_m->name_m+BattleSceneNums::loseMessage);
				enemyPic_m->setExpansion();
				SoundAsset(L"battle_bgm").pause(3.0s);
			}
			SoundAsset(L"battle_bgm").changeTempo((time_m < 300)?1.5:1.0);
		}
		break;
	case BattleState::win:
		//Println(L"正解");
		if (message_m->isPlotAll() && !enemyPic_m->isDraw()) {
			if (round_m == 30) {
				m_data->time = time_m;
				changeScene(BattleSceneNums::nextScene);
			}
			else {				
				state_m = BattleState::select;
				round_m++;
				objects.find(L"RoundWindow")->second->setText(Format(round_m, L"戦目"));
				newEnemy();
			}
		}
		break;
	case BattleState::lose:
		//Println(L"不正解");
		SoundAsset(L"battle_GameOver").play();
		if (message_m->isPlotAll()) {
			m_data->time = 0;
			dataManager_m.writeSaveData();
			SoundAsset(L"battle_bgm").stop();
			changeScene(BattleSceneNums::nextScene);
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
	int rand = enemy_ID_List_m[round_m];
	enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(rand));
	
	// モンタージュファントム
	if (enemy_m->id_m == 16) {
		int rand2;
		do {		
			rand2 = RandomSelect(m_data->defeatedEnemyList);
		} while (rand2 == 16 || rand==22 || rand2 == 29);
		auto monta = make_shared<EnemyData>(dataManager_m.getEnemy(rand2));
		AnswerManager::setCorectAnswer(monta->collectAnswer_m);

		enemyPic_m->setText(Format(L"EnemyGraphics/", enemy_m->id_m, L".png"));
		enemyPic_m->setBigger();

		enemy_m->messages_m.onContact_m = L"モンタージュファントムが現れた！\nモンタージュファントムは" + monta->name_m + L"に変化した！";
		enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"に攻撃を仕掛けた！\nだが倒しきれなかった！";

		message_m->setNewText(enemy_m->messages_m.onContact_m);

		backPic_m->setText(Format(L"BackGround/battle_graphic", Random(1, 5), L".jpg")); // 要修正 enemy_m.bgid

		const Array<String> buttonName = { L"weapon", L"magic",L"special" };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				auto b = objects.find(Format(buttonName[i], j))->second;
				switch (i)
				{
				case 0:
					b->setText(monta->answers_m.weapon_m[j]);
					break;
				case 1:
					b->setText(monta->answers_m.magic_m[j]);
					break;
				case 2:
					b->setText(monta->answers_m.special_m[j]);
					break;
				default:
					break;
				}
			}
		}
	}
	// カリキョン
	else if (enemy_m->id_m == 29) {
		
		int a = Random(10,99);
		int b = Random(1,a);
		String ope = (Random(1) == 0) ? L"+" : L"-";
		int ans = (ope == L"+") ? a + b : a - b;

		AnswerManager::setCorectAnswer(Format(ans));

		enemyPic_m->setText(Format(L"EnemyGraphics/", enemy_m->id_m, L".png"));
		enemyPic_m->setBigger();

		enemy_m->messages_m.onContact_m = Format(L"計算兵器カリキョンが現れた！\n「",a,ope,b,L"は？」");
		enemy_m->messages_m.onPlayerLost_m = Format(L"「この程度の問題を間違えるな」\n計算兵器カリキョンを倒しきれなかった！\n「",a,ope,b,L"は？」");

		message_m->setNewText(enemy_m->messages_m.onContact_m);

		backPic_m->setText(Format(L"BackGround/battle_graphic", Random(1, 5), L".jpg")); // 要修正 enemy_m.bgid

		const Array<String> buttonName = { L"weapon", L"magic",L"special" };
		int nums[9];
		for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
		nums[Random(8)] = ans + 10;
		nums[Random(8)] = ans;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				auto bt = objects.find(Format(buttonName[i], j))->second;
				switch (i)
				{
				case 0:
					bt->setText(Format(nums[i * 3 + j]));
					break;
				case 1:
					bt->setText(Format(nums[i * 3 + j]));
					break;
				case 2:
					bt->setText(Format(nums[i * 3 + j]));
					break;
				default:
					break;
				}
			}
		}

	}
	// 一般的な敵
	else {
		AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

		enemyPic_m->setText(Format(L"EnemyGraphics/", enemy_m->id_m, L".png"));
		enemyPic_m->setBigger();

		message_m->setNewText(enemy_m->messages_m.onContact_m);

		backPic_m->setText(Format(L"BackGround/battle_graphic", Random(1, 5), L".jpg")); // 要修正 enemy_m.bgid

		const Array<String> buttonName = { L"weapon", L"magic",L"special" };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				auto b = objects.find(Format(buttonName[i], j))->second;
				switch (i)
				{
				case 0:
					b->setText(enemy_m->answers_m.weapon_m[j]);
					break;
				case 1:
					b->setText(enemy_m->answers_m.magic_m[j]);
					break;
				case 2:
					b->setText(enemy_m->answers_m.special_m[j]);
					break;
				default:
					break;
				}
			}
		}

	}
}
