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
	const int timeLimit = 100;

	// 正解した時の制限時間の増加量
	const int timeRecovery = 420;

	// Enemy画像の拡大率
	const double scale = 0.4;

	// Enemyのフェードイン/アウトの早さ
	const double fadeIn = 6;
	double fadeOut = 2;

	// 敗北時のEnemyの最大拡大率
	const double maxScale = 2.0;

	// 次のシーン
	const String nextScene = L"Result";

	// 敗北時のメッセージ
	const String loseMessage = L"にやられた！\nクリックで次へすすむ...";

	// メッセージ表示速度
	const int mesSpeed = 2;

	// 間違えた時ボタンが押せなくなる時間
	const int penaltyTime = 60;
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

namespace StateManager {
	bool isGoTitle;
	bool isGameClear;
	bool isGameOver;
	bool isImprove;
	BattleState curentState_m;
	void init() {
		isGoTitle = false;
		isGameOver = false;
		isGameOver = false;
		isImprove = false;
	}
	BattleState update() {
		return curentState_m;
	}
	void setGameOver(){
		isGameOver = true;
	}
}

// 基底クラス
class BattleSceneObject : public Drawable
{
public:
	virtual void update() = 0;
	virtual void setText(String text) = 0;
};

//テキスト付きウィンドウ
class WindowAndText	: public BattleSceneObject
{
protected:
	const Point center_m;
	const String textureAssetName_m;
	Color strColor_m;
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

// タイマー
class Timer : public WindowAndText {
private:
	int time_m;
	int TIME_RECOVERY;
	bool isUpdate;
public:
	Timer(Point center, String textureAssetName, Color c = Palette::Black) :WindowAndText(center,textureAssetName,c),TIME_RECOVERY(BattleSceneNums::timeRecovery)
	{
		time_m = BattleSceneNums::timeLimit;
		isUpdate = false;
	}
	void update() override {
		if (!isUpdate)return;
		{
			time_m--;
			setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m % 60, { 2, L'0' })));
			if (time_m <= 0) { StateManager::setGameOver();	}
			SoundAsset(L"battle_bgm").changeTempo((time_m < 300) ? 1.5 : 1.0);
			strColor_m = ((time_m < 300) ? Palette::Red : Palette::Black);
		}
	}
	void recovery() {
		time_m += TIME_RECOVERY;
	}
	void stop() {
		isUpdate = false;
	}
	void start() {
		isUpdate = true;
	}
	int getTime() {
		return time_m;
	}
};

// 戦闘数
class RoundCounter : public WindowAndText{
private:
	int round_m;
public:
	RoundCounter(Point center, String textureAssetName, Color c = Palette::Black):WindowAndText(center,textureAssetName,c) {
		round_m = -1;
		next();
	}
	void next() {
		round_m++;
		setText(Format(round_m,L"戦目"));
	}
	void update()override {
		if (round_m == 30) {
			StateManager::isGameClear = true;
		}
	}
	bool isGameClear() {
		return round_m > 30;
	}
	int getRound() {
		return round_m;
	}
};

 //メッセージ
class MessageWindow : public WindowAndText,public TextView {
public:
	MessageWindow(Point center, String textureAssetName, Color c = Palette::Black)
		: WindowAndText(center, textureAssetName,c)
		, TextView(L"", Point(210, center.y - 60), 850, 3 , Font(20),BattleSceneNums::mesSpeed, Palette::Black){}
	void update()override {
		TextView::update();
	}
	void draw()const override {
		WindowAndText::draw();
		TextView::draw();
	}
};

//ボタン
class BattleSceneButton : public BasicButton , public BattleSceneObject{
protected:
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
		FontAsset(L"BattleSceneFont").drawCenter(text_m, bPos,color_m);
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

// タイトルへのボタン
class TitleButton : public BattleSceneButton {
public:
	TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black):BattleSceneButton(pos,size,textureAssetName,c) {};
	void onClicked() override {
		StateManager::isGoTitle = true;
	}
};

// 
class NextButton
	: public BattleSceneButton {
public:
	NextButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {};
	void update()override {
		//setStrColor(HSV(System::FrameCount()*2));
	}
	void onClicked() override {
		StateManager::isImprove = true;
	}
};

//画像
class PictureObject : public BattleSceneObject{
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
public:
	PictureObject(String assetName,double scale,Point pos):pos(pos),defaultScale(scale){
		setText(assetName);
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
		aseetName = text;
		setFadeIn();
	}
	void draw()const override {
		Point drawPos = pos + Point(Math::Cos(System::FrameCount()), 0);
		TextureAsset(aseetName).scale(scale).rotate(rad).drawAt(drawPos, Color(Palette::White).setAlpha(static_cast<int>(alpha)));
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

class CutIn : public BattleSceneObject
{
private:
	const Point END_POS = {145,200};
	double alpha_m;
	double scale_m;
	Point pos_m;
	unsigned timer_m;
	enum State{in,center,move,moved} state_m;
	bool isHide;
public:
	CutIn() : pos_m(Window::Center()){
		isHide = true;
	};
	~CutIn(){};
	void setText(String text)override{}
	void init(){
		alpha_m = 100;
		scale_m = 10.0;
		pos_m = Window::Center();
		state_m = State::in;
		isHide = false;
	}
	void hide(){
		isHide = true;
	}
	void update() override {

		if (isHide)return;

		if (alpha_m < 255) alpha_m+=5;

		switch (state_m)
		{
		case State::in:
			if (scale_m > 1.0) {
				scale_m -= 0.3;
			}
			else {
				scale_m = 1.0;
				state_m = State::move;
			}
			break;
		case State::center:
			break;
		case State::move:
		{
			const int spd = 10;
			
			Vec2 v(END_POS - pos_m);
			if (v.length() < spd) {
				pos_m = END_POS;
			}
			else {
				v.setLength(spd);
				pos_m.moveBy(v.asPoint());
			}
			break;
		}
		case State::moved:
			break;
		default:
			break;
		}

		
	};
	void draw()const override{
		if (!isHide) {
			TextureAsset(L"CutInEffect").scale(scale_m).drawAt(pos_m, Color(Palette::White).setAlpha(static_cast<int>(alpha_m)));
		}
	}
};

// アセット登録
void assetRegistration() {

	// フォントアセット登録
	//if (!FontAsset::IsRegistered(L"CommandFont")) {	FontAsset::Register(L"CommandFont", 20);}
	if (!FontAsset::IsRegistered(L"BattleSceneFont")) { FontAsset::Register(L"BattleSceneFont", 20); }

	// テクスチャアセット登録
	if (!TextureAsset::IsRegistered(L"mesWindow")) { TextureAsset::Register(L"mesWindow", L"/501"); }
	if (!TextureAsset::IsRegistered(L"miniMesWindow")) { TextureAsset::Register(L"miniMesWindow", L"/502"); }
	if (!TextureAsset::IsRegistered(L"battleButton")) { TextureAsset::Register(L"battleButton", L"/500"); }
	if (!TextureAsset::IsRegistered(L"CutInEffect")) { TextureAsset::Register(L"CutInEffect", L"/503"); }
	for (int i = 1; i <= 5; i++) {
		TextureAsset::Register(Format(L"battleBack", i), Format(L"/", (510 + i)));
	}

	// サウンドアセット登録
	SoundAsset::Register(L"battle_corect", L"/521");
	SoundAsset::Register(L"battle_incorect", L"/522");
	SoundAsset::Register(L"battle_bgm", L"/520");
	SoundAsset::Register(L"bettle_GameOver", L"/523");
	SoundAsset::Register(L"bettle_entry", L"/524");
}

// Enemyのリスト
class EnemyIdList {
private:
	int list_m[31];
public:
	EnemyIdList() {
		for (int i = 1; i <= 30; i++)list_m[i] = i;
		swap(list_m[16], list_m[27]);
		swap(list_m[22], list_m[28]);
		for (int i = 1; i <= 26; i++) {
			swap(list_m[i], list_m[Random(1, 26)]);
		}
		swap(list_m[27], list_m[Random(15, 29)]);
		swap(list_m[28], list_m[Random(15, 29)]);
		swap(list_m[29], list_m[Random(15, 29)]);
	}
	int get(int id) {
		return (0 < id && id < 31) ? list_m[id] : 0;
	}	
};

}
}

/***********************************************************************************************************************/

Battle::Battle(){};

Battle::~Battle(){};

void Battle::init(){
	//各種定数
	const int tx = 5;
	const int ty = 5;	
	const int windowPosY = 80;

	// 背景色変更
	Graphics::SetBackground(Palette::Lightslategray);

	// ボタンマネージャのクリア
	ButtonManager::clearAll();
	ButtonManager::update();

	// GameData 初期化
	m_data->resetEnemyList();
	m_data->time = 0;

	// アセット登録
	assetRegistration();

	// BGM再生
	SoundAsset(L"battle_bgm").setLoop(true);
	SoundAsset(L"battle_bgm").play();
	
	// 各種初期化
	state_m = BattleState::Start;
	AnswerManager::init();
	StateManager::init();
	incorect = false;

	// 戦闘数
	roundCounter_m = make_shared<RoundCounter>(Point(100, windowPosY ), L"miniMesWindow");
	addObject(roundCounter_m, L"RoundWindow", 10);

	// メッセージ
	message_m = make_shared<MessageWindow>(Point(Window::Width() / 2, windowPosY), L"mesWindow");
	addObject(message_m, L"messageWindow", 10);
	message_m->setNewText(L"準備はいいですか?\nStartを押すとゲームが始まります!");

	// タイマー
	timer_m = make_shared<Timer>(Point(Window::Width() - 100,windowPosY ), L"miniMesWindow");
	addObject(timer_m, L"timeWindow", 10);

	// Button
	const int width = 420;
	const int height = 60;
	const Array<String> buttonName = { L"weapon", L"magic",L"special" };
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 3; j++) {
			auto b = std::make_shared<BattleSceneButton>(BattleSceneButton({ Window::Width() / 2 -width/2  + (width+tx) * (i - 1), Window::Height() - (height+ty) * (3-j) },Size(width,height),L"battleButton"));
			b->setStrColor(Palette::Black);
			b->setText(L"Start");
			CommantButton_m[3*i+j] = b;
			ButtonManager::add(b);
			addObject(b, Format(buttonName[i],j), 10);
		}
	}
	AnswerManager::setCorectAnswer(L"Start");

	// タイトルボタン
	auto titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	titleButton->setText(L"タイトルにもどる");
	addObject(titleButton,L"titleButton", 12);
	ButtonManager::add(titleButton);

	// 次へボタン
	nextButton = make_shared<NextButton>(Point(Window::Width() / 2 - width / 2, Window::Height() - height * 4 - tx * 4), Size(width, height), L"battleButton");
	nextButton->setText(L"次にすすむ");
	addObject(nextButton, L"nextButton", 12);
	ButtonManager::add(nextButton);
	nextButton->hide();
	nextButton->setStrColor(Palette::Blue);

	// 背景画像
	backPic_m = make_shared<PictureObject>(L"battleBack5",1.0,Window::Center());
	addObject(backPic_m, L"background", 1);

	// カットイン
	cutIn_m = make_shared<CutIn>();
	addObject(cutIn_m, L"CutIn", 15);

	// Enemy ID List
	enemyList_m = make_shared<EnemyIdList>();

	//enemyData
	TextureAsset::Register(L"logo", L"/201");
	enemyPic_m = make_shared<PictureObject>(L"logo", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemyPic_m, L"enemy",5);

};

void Battle::update(){
	ClearPrint();
	for_each(objects.begin(), objects.end(), [](auto pare) {pare.second->update(); });

	//タイトルに戻るボタン
	if (StateManager::isGoTitle) { nextScene(L"Title"); }

	if (StateManager::isGameOver) { state_m = BattleState::GameOver; }

	if (StateManager::isGameClear) { state_m = BattleState::GameClear; }

	//メッセージ速度変更
	message_m->setIntervalIncrease((Input::MouseL.pressed) ? 0 : 3);

	// フェードアウト速度変更
	BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

	if (StateManager::isImprove) { state_m = BattleState::EnemyEntry; }

	switch (state_m)
	{

	// ゲーム開始時
	case BattleState::Start:
	{
		auto ans = AnswerManager::checkAnswer();
		if (ans == Answers::correct) {
			state_m = BattleState::EnemyEntry;
			canAnswer = true;
		}
	}
		break;

	// 敵が登場するときの処理
	case BattleState::EnemyEntry:	
		roundCounter_m->next();
		//round_m++;
		//objects.find(L"RoundWindow")->second->setText(Format(round_m, L"戦目"));
		newEnemy();
		state_m = BattleState::Answer;
		nextButton->hide();
		StateManager::isImprove = false;
		timer_m->start();
		break;

	// 回答
	case BattleState::Answer:

			// 回答
			{
				// ボタンの誤動作防止
				/*if (!canAnswer) {
					if (Input::MouseL.released) {
						canAnswer = true;
					}
					AnswerManager::init();				
					break;
				}*/

				auto ans = AnswerManager::checkAnswer();
				// 正解時
				if (ans == Answers::correct) {
					state_m = BattleState::Corect;
				}				
				// 不正解時
				else if (ans == Answers::incorrect) {
					state_m = BattleState::Incorect;
				}
			}		
			if (incorect && message_m->isAllPoltAndOverTime()) {
				message_m->setNewText(enemy_m->messages_m.onContact_m);
				incorect = false;		
			}
			break;

	// 不正解を選んで選択できなくなっている間の処理
	case BattleState::CanNotAnswer:
		penalty_m--;
		if (penalty_m == 0) {
			for (auto& b : CommantButton_m) { b->setStrColor(Palette::Black); }
			AnswerManager::init();
			state_m = BattleState::Answer;
		}
		break;

	// 不正解を選んだ瞬間の処理
	case BattleState::Incorect:
		message_m->setNewText(enemy_m->messages_m.onPlayerLost_m);
		AnswerManager::init();
		SoundAsset(L"battle_incorect").playMulti();
		incorect = true;

		penalty_m = BattleSceneNums::penaltyTime;
		for (auto& b : CommantButton_m) { b->setStrColor(Palette::Red); }
		state_m = BattleState::CanNotAnswer;
		break;

	//正解を選んだ瞬間の処理
	case BattleState::Corect:
	{
		message_m->setNewText(enemy_m->messages_m.onPlayerWon_m);
		enemyPic_m->setFadeOut();
		enemyPic_m->setRoolAndSmall();
		//backPic_m->setFadeOut();

		timer_m->recovery();
		//time_m += BattleSceneNums::timeRecovery;

		dataManager_m.setSaveData(enemy_m->id_m, true);
		m_data->addEnemy(enemy_m->id_m);

		SoundAsset(L"battle_corect").playMulti();

		nextButton->show();

		canAnswer = false;
		timer_m->stop();
		state_m = BattleState::ExitEnemy;
		break;
	}

	// 正解して敵が消えていく間の処理
	case BattleState::ExitEnemy:
		/*if (message_m->isPlotAll() && !enemyPic_m->isDraw()) {
			state_m = BattleState::AcceptedClick;
		}*/
		break;

	// 敵が消えてからクリックを待つ処理
	case BattleState::AcceptedClick:
		/*if(Input::MouseL.pressed ) {
			incorect = false;
			if (roundCounter_m->isGameClear()) {
				nextScene(BattleSceneNums::nextScene);
			}
			else {
				state_m = BattleState::EnemyEntry;				
			}
		}*/
		break;

	case BattleState::TimeOver:
	case BattleState::GameOver:
		// GameOver
		if (message_m->isPlotAll() && Input::MouseL.pressed ) {
				nextScene(BattleSceneNums::nextScene);
		}		
		break;

	case BattleState::GameClear:
		nextScene(BattleSceneNums::nextScene);
		break;

	default:
		break;
	}
};

void Battle::draw()const{
	drawList_m.drawAll();
	effect_m.update();
};

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, String  name, int layer) {
	objects.insert(std::make_pair(name, obj));
	drawList_m.add(obj, layer);
}

void Battle::nextScene(String sceneName) {
	m_data->time = timer_m->getTime();
	dataManager_m.writeSaveData();
	SoundAsset(L"battle_bgm").stop();
	changeScene(sceneName);
}

void Battle::newEnemy() {

	// 次の敵のデータを取得
	enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(enemyList_m->get(roundCounter_m->getRound())));

	int id = enemy_m->id_m;

	// 特殊モンスター　モンタージュファントム
	if (id == 16) {
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
	else if (id == 29) {
		
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
		enemy_m->messages_m.onPlayerLost_m = Format(L"「この程度の問題を間違えるな」\n計算兵器カリキョンを倒しきれなかった！");//\n「", a, ope, b, L"は？」");

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
	enemyPic_m->setText(Format(L"Enemy",enemy_m->id_m));
	enemyPic_m->setBigger();

	// 背景画像設定
	backPic_m->setText(Format(L"battleBack", enemy_m->bgid_m));	

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

	// 特殊な敵の時カットインを入れる	
	if (id == 16 || id == 22 || id == 29) { cutIn_m->init(); }
	else{ cutIn_m->hide(); }


	/*if(id == 2 || id == 17 || id==18){
		enemy_m->messages_m.onPlayerWon_m.append(L"クリックで次へすすむ...");
	}
	else {
		enemy_m->messages_m.onPlayerWon_m.append(L"\nクリックで次へすすむ...");
	}*/
	
	SoundAsset(L"bettle_entry").setSpeed(0.5);
	SoundAsset(L"bettle_entry").play();
}
