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
	const int timeLimit = 1800;

	// 正解した時の制限時間の増加量
	const int timeRecovery = 420;

	// Enemy画像の拡大率
	const double scale = 0.4;

	// Enemyのフェードイン/アウトの早さ
	const double fadeIn = 6;
	const double fadeOut = 2;

	// 敗北時のEnemyの最大拡大率
	const double maxScale = 2.0;

	// 次のシーン
	const String nextScene = L"Result";

	// 敗北時のメッセージ
	const String loseMessage = L"にやられた！";

	// メッセージ表示速度
	const int mesSpeed = 2;
}

//回答
enum Answers { correct, incorrect, not };
namespace AnswerManager{
	static String corectAnswer = L"";
	static Answers playersAnswer;
	static bool isAnswered;
	static void init() {
		isAnswered = false;
	}
	static void setCorectAnswer(String corect){
		corectAnswer = corect;
		isAnswered = false;
	}
	static void answer(String ans) {
		playersAnswer = (ans == corectAnswer) ? Answers::correct : Answers::incorrect;
		isAnswered = true;
	}
	static Answers checkAnswer() {
		if (isAnswered == false) { playersAnswer = Answers::not; }
		return playersAnswer;
	}
};

bool isGoTitle;
bool isGoToTitle() {
	return isGoTitle;
}

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
	const Point center_m;
	const String textureAssetName_m;
	const Color strColor_m;
	String str_m;
public:
	WindowAndText(Point center,String textureAssetName,Color c = Palette::Black) : center_m(center), textureAssetName_m(textureAssetName), strColor_m(c){};
	void update()override {};
	void setText(String text)override {	
		str_m = text;
	}
	void draw()const override {
		TextureAsset(textureAssetName_m).drawAt(center_m);
		FontAsset(L"BattleSceneFont").drawCenter(str_m, center_m,strColor_m);
	}
};

//ボタン
class BattleSceneButton : public BasicButton , public BattleSceneObject{
private:
	const Size size;
	const Point pos;
	const Point center;
	String text_m;
	const String textureAssetName_m;
	Color color_m;	//文字色
public:
	BattleSceneButton(Point pos,Size size,String textureAssetName,Color c = Palette::Black)
		:BasicButton(Shape(Rect(pos, size))), size(size), pos(pos), center(pos + size / 2),textureAssetName_m(textureAssetName),color_m(c){};
	void draw() const
	{
		Point bPos = center;
		double mag = 1.0;
		switch (getState()) {
		case State::MOUSE_OVER:
			bPos.moveBy({0,-2});
			mag = 1.01;
			break;
		case State::LEFT:
		case State::PRESSED:
		case State::RELEASED:
		default:
			break;
		}
		TextureAsset(textureAssetName_m).scale(mag).drawAt(bPos);
		FontAsset(L"CommandFont").drawCenter(text_m, bPos,color_m);
	}
	void setText(String text)override {
		text_m = text;
	}
	void onClicked()override {
		AnswerManager::answer(text_m);
	}
	void update()override {}
	void setStrColor(Color c) {
		color_m = c;
	}
};

class TitleButton : public BattleSceneButton {
public:
	TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black):BattleSceneButton(pos,size,textureAssetName,c) {};
	void onClicked() override{
		isGoTitle = true;
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
	//各種定数
	const String assetPath = L"Asset/";
	const int tx = 5;
	const int ty = 5;	

	// 背景色変更
	Graphics::SetBackground(Palette::Lightslategray);

	// ボタンマネージャのクリア
	ButtonManager::clearAll();
	ButtonManager::update();

	// GameData 初期化
	m_data->resetEnemyList();
	m_data->time = 0;

	// フォントアセット登録
	if (!FontAsset::IsRegistered(L"CommandFont")) {	FontAsset::Register(L"CommandFont", 20);}
	if (!FontAsset::IsRegistered(L"BattleSceneFont")) {	FontAsset::Register(L"BattleSceneFont", 20);}

	// テクスチャアセット登録
	TextureAsset::Register(L"mesWindow", assetPath + L"message_graphic.png");
	TextureAsset::Register(L"miniMesWindow", assetPath + L"small_message_graphic.png");
	TextureAsset::Register(L"battleButton", assetPath + L"window_graphic.png");
	/*for (int i = 1; i <= 5; i++) {
		TextureAsset::Register(Format(L"battleBack",i), Format(assetPath,"BackGround/battle_graphic",i,L".jpg"));
	}*/

	// サウンドアセット登録
	SoundAsset::Register(L"battle_corect", assetPath + L"crrect_answer3.mp3");
	SoundAsset::Register(L"battle_incorect", assetPath + L"powerdown07.mp3");
	SoundAsset::Register(L"battle_bgm", assetPath + L"bgm_maoudamashii_neorock49.ogg");
	SoundAsset::Register(L"bettle_GameOver", assetPath + L"damage7.mp3");

	// BGM再生
	SoundAsset(L"battle_bgm").setLoop(true);
	SoundAsset(L"battle_bgm").play();
	
	// 各種初期化
	round_m = 1;
	time_m = BattleSceneNums::timeLimit;
	state_m = BattleState::select;
	AnswerManager::init();
	isGoTitle = false;
	incorect = false;

	// Window
	const int windowPosY = 80;
	auto r = WindowAndText({ 100,windowPosY }, L"miniMesWindow");
	r.setText(L"1戦目");
	addObject(make_shared<WindowAndText>(r), L"RoundWindow", 10);
	auto m = WindowAndText({ Window::Width() / 2,windowPosY }, L"mesWindow");
	addObject(make_shared<WindowAndText>(m), L"messageWindow", 10);
	auto t = WindowAndText({ Window::Width() - 100,windowPosY }, L"miniMesWindow");
	addObject(make_shared<WindowAndText>(t), L"timeWindow", 10);

	// message
	message_m = make_shared<TextView>(L"testMessage", Point(210,windowPosY-60) , 870, 3, Font(20), BattleSceneNums::mesSpeed, Palette::Black);
	drawList_m.add(message_m,11);
	message_m->setAllPlotTime(10);

	// Button
	const int width = 420;
	const int height = 60;
	const Array<String> buttonName = { L"weapon", L"magic",L"special" };
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 3; j++) {
			auto b = std::make_shared<BattleSceneButton>(BattleSceneButton({ Window::Width() / 2 -width/2  + (width+tx) * (i - 1), Window::Height() - (height+ty) * (3-j) },Size(width,height),L"battleButton"));
			b->setStrColor(Palette::Black);
			ButtonManager::add(b);
			addObject(b, Format(buttonName[i],j), 10);
		}
	}

	titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	titleButton->setText(L"タイトルにもどる");
	addObject(titleButton,L"titleButton", 12);
	ButtonManager::add(titleButton);

	// 背景画像
	backPic_m = make_shared<PictureObject>(L"null",1.0,Window::Center());
	addObject(backPic_m, L"background", 1);

	// Enemy ID List
	// 16 22 29 30が特殊
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
	enemyPic_m = make_shared<PictureObject>(L"null", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemyPic_m, L"enemy",5);
	newEnemy();

};

void Battle::update(){
	ClearPrint();
	for_each(objects.begin(), objects.end(), [](auto pare) {pare.second->update(); });
	message_m->update();

	if (isGoTitle) {
		nextScene(L"Title");
	}

	switch (state_m)
	{
	case BattleState::select:
		// 回答
		{
			auto ans = AnswerManager::checkAnswer();
			
			// 正解時
			if (ans == Answers::correct) {
				state_m = BattleState::win;
				message_m->setNewText(enemy_m->messages_m.onPlayerWon_m);
				enemyPic_m->setFadeOut();
				enemyPic_m->setRoolAndSmall();
				backPic_m->setFadeOut();

				time_m += BattleSceneNums::timeRecovery;

				dataManager_m.setSaveData(enemy_m->id_m, true);
				m_data->addEnemy(enemy_m->id_m);
				
				SoundAsset(L"battle_corect").play();
			}
			// 不正解時
			else if (ans == Answers::incorrect) {
				message_m->setNewText(enemy_m->messages_m.onPlayerLost_m);
				AnswerManager::init();
				SoundAsset(L"battle_incorect").playMulti();
				incorect = true;
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
			}
			SoundAsset(L"battle_bgm").changeTempo((time_m < 300)?1.5:1.0);
		}
		if (incorect && message_m->isAllPoltAndOverTime()) {
			//message_m->setIntervalIncrease(0);
			message_m->setNewText(enemy_m->messages_m.onContact_m);
			//message_m->setPlotAll();
			incorect = false;
		}

		break;
	// 正解時
	case BattleState::win:
		if (message_m->isAllPoltAndOverTime() && !enemyPic_m->isDraw() ) {
			incorect = false;
			if (round_m == 30) {
				nextScene(BattleSceneNums::nextScene);
			}
			else {				
				state_m = BattleState::select;
				round_m++;
				objects.find(L"RoundWindow")->second->setText(Format(round_m, L"戦目"));
				newEnemy();
			}
		}
		break;

	// GameOver
	case BattleState::lose:
		SoundAsset(L"bettle_GameOver").play();
		if (message_m->isAllPoltAndOverTime()) {
			nextScene(BattleSceneNums::nextScene);
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

void Battle::nextScene(String sceneName) {
	m_data->time = time_m;
	dataManager_m.writeSaveData();
	SoundAsset(L"battle_bgm").stop();
	changeScene(sceneName);
}

void Battle::newEnemy() {

	// 次の敵のデータを取得
	enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(2));// enemy_ID_List_m[round_m]));

	// 特殊モンスター　モンタージュファントム
	if (enemy_m->id_m == 16) {
		int rand;
		do {		
			rand = RandomSelect(m_data->defeatedEnemyList);
		} while (rand == 16 || rand == 22 || rand == 29);		//特殊モンスターはコピーしない

		// コピーするモンスターのデータを取得
		auto monta = make_shared<EnemyData>(dataManager_m.getEnemy(rand));

		// 登場メッセージを設定
		enemy_m->messages_m.onContact_m = L"モンタージュファントムが現れた！\nモンタージュファントムは" + monta->name_m + L"に変化した！";

		// 攻撃失敗時のメッセージを設定
		enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"に攻撃を仕掛けた！\nだが倒しきれなかった！";

		// 正解をコピー
		enemy_m->collectAnswer_m = monta->collectAnswer_m;

		// 選択肢をコピー
		for (int i = 0; i < 3; i++) {
			enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
			enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
			enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
		}
	}

	// 特殊モンスター　カリキョン
	else if (enemy_m->id_m == 29) {
		
		// 式と答えを設定
		int a = Random(10,99);
		int b = Random(1,a);
		String ope = (Random(1) == 0) ? L"+" : L"-";
		int ans = (ope == L"+") ? a + b : a - b;

		// 正解を設定
		enemy_m->collectAnswer_m = Format(ans);

		// 登場メッセージを設定
		enemy_m->messages_m.onContact_m = Format(L"計算兵器カリキョンが現れた！\n「",a,ope,b,L"は？」");

		// 攻撃失敗時のメッセージを設定
		enemy_m->messages_m.onPlayerLost_m = Format(L"「この程度の問題を間違えるな」\n計算兵器カリキョンを倒しきれなかった！\n「",a,ope,b,L"は？」");

		// 選択肢をランダムに用意
		int nums[9];
		for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
		nums[Random(8)] = ans + 10;		// 正解より10大きい選択肢を用意
		nums[Random(8)] = ans;			// 正解を用意
		
		for (int i = 0; i < 3; i++) {
			enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
			enemy_m->answers_m.magic_m[i] = Format(nums[3+i]);
			enemy_m->answers_m.special_m[i] = Format(nums[6+i]);
		}
	}

	// Enemy画像設定
	enemyPic_m->setText(Format(L"EnemyGraphics/", enemy_m->id_m, L".png"));						// 後でAssetに変更
	enemyPic_m->setBigger();

	// 背景画像設定
	backPic_m->setText(Format(L"BackGround/battle_graphic", enemy_m->bgid_m, L".jpg"));			//後でAssetに変更

	// 正解を登録
	AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

	// 登場メッセージを設定
	message_m->setNewText(enemy_m->messages_m.onContact_m);

	// ボタンに選択しを設定
	for (int i = 0; i < 3; i++) {
		objects.find(Format(L"weapon", i))->second->setText(enemy_m->answers_m.weapon_m[i]);
		objects.find(Format(L"magic",i))->second->setText(enemy_m->answers_m.magic_m[i]);
		objects.find(Format(L"special",i))->second->setText(enemy_m->answers_m.special_m[i]);
	}
}
