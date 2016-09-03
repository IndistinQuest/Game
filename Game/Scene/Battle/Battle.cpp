#include"Battle.h"
#include"..\..\Drawable\Drawable.h"
#include"..\..\Button\BasicButton.h"
#include"../../Button/ButtonManager.h"

#include"../../Data/DataManager.h"

#include"AnswerManager.h"

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
			double fadeOut = 2;

			// 敗北時のEnemyの最大拡大率
			const double maxScale = 2.0;

			// 次のシーン
			const String nextScene = L"Result";

			// 敗北時のメッセージ
			const String loseMessage = L"にやられた！";

			const String StartMes = L"準備はいいですか?\nStartを押すとゲームが始まります!";

			// メッセージ表示速度
			const int mesSpeed = 2;

			// 間違えた時ボタンが押せなくなる時間
			const int penaltyTime = 120;
		}

		class StateManager {
		private:
			static bool isGoTitle;
			static bool isGameClear;
			static bool isTimeOver;
			static bool isImprove;
			static BattleState curentState_m;
		public:
			static void init() {
				isGoTitle = false;
				isGameClear = false;
				isTimeOver = false;
				isImprove = false;
				curentState_m = BattleState::Start;
			}

			static void update() {

				switch (curentState_m)
				{
				case BattleState::Start:
					if (isImprove) {
						curentState_m = BattleState::EnemyEntry;
					}
					break;

					// 敵が登場するときの処理
				case BattleState::EnemyEntry:
					curentState_m = BattleState::Answer;
					break;

					// 回答
				case BattleState::Answer:
				{
					auto ans = AnswerManager::checkAnswer();
					// 正解時
					if (ans == Answers::correct) {
						curentState_m = BattleState::Corect;
					}
					// 不正解時
					else if (ans == Answers::incorrect) {
						curentState_m = BattleState::Incorect;
					}
				}
				break;

				// 不正解を選んで選択できなくなっている間の処理
				case BattleState::CanNotAnswer:
					if (isImprove) {
						curentState_m = BattleState::Answer;
					}
					break;

					// 不正解を選んだ瞬間の処理
				case BattleState::Incorect:
					curentState_m = BattleState::CanNotAnswer;
					break;

					//正解を選んだ瞬間の処理
				case BattleState::Corect:
					curentState_m = BattleState::ExitEnemy;
					break;

					// 正解して敵が消えていく間の処理
				case BattleState::ExitEnemy:
					if (StateManager::isImprove) {
						curentState_m = BattleState::CheckGameClear;
					}
					break;

				case BattleState::CheckGameClear:
					curentState_m = BattleState::EnemyEntry;
					break;

					// 時間切れになった瞬間の処理
				case BattleState::TimeOver:
					curentState_m = BattleState::GameOver;
					break;

					// ゲームオーバーになった時の処理
				case BattleState::GameOver:
					if (isImprove) {
						curentState_m = BattleState::GoToResult;
					}
					break;

				default:
					break;
				}


				if (isTimeOver && curentState_m != BattleState::GameOver && curentState_m != BattleState::GoToResult) { curentState_m = BattleState::TimeOver; }
				if (isGoTitle) { curentState_m = BattleState::BackToTitle; }
				if (isGameClear) { curentState_m = BattleState::GoToResult; }

				isImprove = false;
			}

			static BattleState getState() {
				return curentState_m;
			}

			static void setNextState(BattleState next) {
				curentState_m = next;
			}

			static void setBackToTitle() {
				isGoTitle = true;
			}
			static void setTimeOver() {
				isTimeOver = true;
			}
			static void setGameClear() {
				isGameClear = true;
			}
			static void goToNext() {
				isImprove = true;
			}
		};
		bool StateManager::isGoTitle = false;
		bool StateManager::isGameClear = false;
		bool StateManager::isTimeOver = false;
		bool StateManager::isImprove = false;
		BattleState StateManager::curentState_m = BattleState::Start;


		// 基底クラス
		class BattleSceneObject : public Drawable
		{
		public:
			virtual void update() = 0;
		};

		//テキスト付きウィンドウ
		class WindowAndText : public BattleSceneObject
		{
		protected:
			const Point center_m;
			const String textureAssetName_m;
			Color strColor_m;
			String str_m;
		public:
			WindowAndText(Point center, String textureAssetName, Color c = Palette::Black) : center_m(center), textureAssetName_m(textureAssetName), strColor_m(c) {};
			void update()override {};
			void setText(String text){
				str_m = text;
			}
			void draw()const override {
				TextureAsset(textureAssetName_m).drawAt(center_m);
				FontAsset(L"BattleSceneFont").drawCenter(str_m, center_m, strColor_m);
			}
		};

		// タイマー
		class Timer : public WindowAndText {
		private:
			int time_m;
			int TIME_RECOVERY;
		public:
			Timer(Point center, String textureAssetName, Color c = Palette::Black) :WindowAndText(center, textureAssetName, c), TIME_RECOVERY(BattleSceneNums::timeRecovery)
			{
				time_m = BattleSceneNums::timeLimit;
				setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m % 60, { 2, L'0' })));
			}
			void update() override {

				switch (StateManager::getState()) {
				case BattleState::Answer:
				case BattleState::CanNotAnswer:
					time_m--;
					if (time_m <= 0) { StateManager::setTimeOver(); }	
					SoundAsset(L"battle_bgm").changeTempo((time_m < 300) ? 1.5 : 1.0);
					setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m % 60, { 2, L'0' })));
					strColor_m = ((time_m < 300) ? Palette::Red : Palette::Black);
					break;
				case BattleState::Corect:
					recovery();
					break;
				default:
					break;

				}
				
			}
			void recovery() {
				time_m += TIME_RECOVERY;
			}

			int getTime() {
				return time_m;
			}
		};

		// 戦闘数
		class RoundCounter : public WindowAndText {
		private:
			int round_m;
		public:
			RoundCounter(Point center, String textureAssetName, Color c = Palette::Black) :WindowAndText(center, textureAssetName, c) {
				round_m = -1;
				next();
			}
			void next() {
				round_m++;
				setText(Format(round_m, L"戦目"));
			}
			void update()override {}
			bool isGameClear() {
				return round_m >= 30;
			}
			int getRound() {
				return round_m;
			}
		};

		//メッセージ
		class MessageWindow : public WindowAndText, public TextView {
		private:
			std::shared_ptr<EnemyData> enemy_m;
			bool incorect_m;
		public:
			MessageWindow(Point center, String textureAssetName, Color c = Palette::Black)
				: WindowAndText(center, textureAssetName, c)
				, TextView(L"", Point(210, center.y - 60), 850, 3, Font(20), BattleSceneNums::mesSpeed, Palette::Black) {
				setNewText(BattleSceneNums::StartMes);
				incorect_m = false;
			}
			void update()override {
				setIntervalIncrease((Input::MouseL.pressed) ? 0 : 3); //メッセージ速度変更

				switch (StateManager::getState())
				{
				case BattleState::Answer:
					if (incorect_m && isAllPoltAndOverTime()) {
						setNewText(enemy_m->messages_m.onContact_m);
						incorect_m = false;
					}
					break;
				case BattleState::EnemyEntry:
					setNewText(enemy_m->messages_m.onContact_m);
					incorect_m = false;
					break;
				case BattleState::TimeOver:
					setNewText(enemy_m->name_m + BattleSceneNums::loseMessage);
					break;
				case BattleState::Corect:
					setNewText(enemy_m->messages_m.onPlayerWon_m);
					break;
				case BattleState::Incorect:
					setNewText(enemy_m->messages_m.onPlayerLost_m);
					incorect_m = true;
					break;
				default:
					break;
				}

				TextView::update();
			}
			void draw()const override {
				WindowAndText::draw();
				TextView::draw();
			}
			void setEnemy(std::shared_ptr<EnemyData> e) {
				enemy_m = e;
			}
		};

		//ボタン
		class BattleSceneButton : public BasicButton, public BattleSceneObject {
		protected:
			const Size size;
			const Point pos;
			const Point center;
			String text_m;
			const String textureAssetName_m;
			Color color_m;	//文字色
		public:
			BattleSceneButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black)
				:BasicButton(Shape(Rect(pos, size))), size(size), pos(pos), center(pos + size / 2), textureAssetName_m(textureAssetName), color_m(c) {};
			void draw() const
			{
				Point bPos = center;
				double mag = 1.0;
				switch (getState()) {
				case State::MOUSE_OVER:
					bPos.moveBy({ 0,-2 });
					mag = 1.01;
					break;
				case State::LEFT:
				case State::PRESSED:
				case State::RELEASED:
				default:
					break;
				}
				TextureAsset(textureAssetName_m).scale(mag).drawAt(bPos);
				FontAsset(L"BattleSceneFont").drawCenter(text_m, bPos, color_m);
			}
			void setText(String text){
				text_m = text;
			}
			void onClicked()override {
				// AnswerManager::answer(text_m);
			}
			void update()override {}
			void setStrColor(Color c) {
				color_m = c;
			}
		};

		class AnswerButton : public BattleSceneButton {
		public:
			AnswerButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {};
			void onClicked()override {
				AnswerManager::answer(text_m);
			}
		};

		// タイトルへのボタン
		class TitleButton : public BattleSceneButton {
		public:
			TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {
				setText(L"タイトルにもどる");
			};
			void onClicked() override {
				StateManager::setBackToTitle();
			}
		};

		// 次へ進むボタン
		class NextButton
			: public BattleSceneButton {
		public:
			NextButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {
				setText(L"次にすすむ");
				hide();
				setStrColor(Palette::Blue);
			};
			void update()override {
				switch (StateManager::getState())
				{
				case BattleState::ExitEnemy:
				case BattleState::GameOver:
					show();
					break;
				default:
					hide();
					break;
				}

			}
			void onClicked() override {
				StateManager::goToNext();
			}
		};

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
		public:
			PictureObject(String assetName, double scale, Point pos) :pos(pos), defaultScale(scale) {
				changeTexture(assetName);
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
			void changeTexture(String assetname) {
				aseetName = assetname;
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
			void setExpansion() {
				isExpansion = true;
			}
		};

		class CutIn : public BattleSceneObject
		{
		private:
			const Point END_POS = { 145,200 };
			double alpha_m;
			double scale_m;
			Point pos_m;
			unsigned timer_m;
			enum State { in, center, move, moved } state_m;
			bool isHide;
		public:
			CutIn() : pos_m(Window::Center()) {
				isHide = true;
			};
			~CutIn() {};
			void init() {
				alpha_m = 100;
				scale_m = 10.0;
				pos_m = Window::Center();
				state_m = State::in;
				isHide = false;
			}
			void hide() {
				isHide = true;
			}
			void update() override {

				if (isHide)return;

				if (alpha_m < 255) alpha_m += 5;

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
			void draw()const override {
				if (!isHide) {
					TextureAsset(L"CutInEffect").scale(scale_m).drawAt(pos_m, Color(Palette::White).setAlpha(static_cast<int>(alpha_m)));
				}
			}
		};

		// アセット登録
		void assetRegistration() {

			// フォントアセット登録
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

		// サウンド
		class SoundPlayer : public BattleSceneObject {
		public:
			SoundPlayer() {
				SoundAsset(L"battle_bgm").setLoop(true);
				SoundAsset(L"battle_bgm").play();
			}
			~SoundPlayer() {
				SoundAsset(L"battle_bgm").stop();
			}
			void update()override {
				switch (StateManager::getState())
				{
					// 敵が登場するときの処理
				case BattleState::EnemyEntry:
					// 敵登場時の効果音再生
					SoundAsset(L"bettle_entry").setSpeed(0.5);
					SoundAsset(L"bettle_entry").play();
					break;

					// 不正解を選んだ瞬間の処理
				case BattleState::Incorect:
					SoundAsset(L"battle_incorect").playMulti();
					break;

					//正解を選んだ瞬間の処理
				case BattleState::Corect:
					SoundAsset(L"battle_corect").playMulti();
					break;

					// 時間切れになった瞬間の処理
				case BattleState::TimeOver:
					SoundAsset(L"bettle_GameOver").play();
				default:
					break;
				}
			}
			void draw()const override {}
		};

		// 回答のボタン
		class AnswerButtons : public BattleSceneObject {
		private:
			//std::shared_ptr<EnemyData> enemy_m;
			std::shared_ptr<AnswerButton> buttons_m[9];
			int penalty_m;
		public:
			AnswerButtons() {
				const int tx = 5, ty = 5;
				const int width = 420;
				const int height = 60;
				//const Array<String> buttonName = { L"weapon", L"magic",L"special" };
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						auto b = std::make_shared<AnswerButton>(AnswerButton({ Window::Width() / 2 - width / 2 + (width + tx) * (i - 1), Window::Height() - (height + ty) * (3 - j) }, Size(width, height), L"battleButton"));
						b->setStrColor(Palette::Black);
						b->setText(L"Start");
						buttons_m[3 * i + j] = b;
						ButtonManager::add(b);
					}
				}
				AnswerManager::setCorectAnswer(L"Start");

				penalty_m = 0;
			}
			void update()override {
				switch (StateManager::getState())
				{

					// 不正解を選んで選択できなくなっている間の処理
				case BattleState::CanNotAnswer:
					penalty_m--;
					if (penalty_m == 0) {
						for (auto& b : buttons_m) { b->setStrColor(Palette::Black); }
						StateManager::goToNext();
					}
					break;

					// 不正解を選んだ瞬間の処理
				case BattleState::Incorect:
					penalty_m = BattleSceneNums::penaltyTime;
					for (auto& b : buttons_m) { b->setStrColor(Palette::Red); }
					break;
				default:
					break;
				}
			};
			void draw()const override {
				for (auto b : buttons_m) { b->draw(); }
			}
			void setAnswers(shared_ptr<EnemyData> enemy) {
				// ボタンに選択しを設定
				for (int i = 0; i < 3; i++) {
					buttons_m[i]->setText(enemy->answers_m.weapon_m[i]);
					buttons_m[i + 3]->setText(enemy->answers_m.magic_m[i]);
					buttons_m[i + 6]->setText(enemy->answers_m.special_m[i]);
				}
			}
		};

		class EnemyManager : public BattleSceneObject {
		private:
			std::shared_ptr<EnemyData> enemy_m;				// Enemyデータ
			DataManager dataManager_m;						//
			std::shared_ptr<PictureObject> enemyPic_m;		// Enemy画像

			int enemyIdList_m[31];		// 登場順リスト

			std::shared_ptr<CutIn> cutIn_m;					// カットイン
			std::shared_ptr<PictureObject> backPic_m;		// 背景画像
			//std::shared_ptr<RoundCounter> round_m;			// 戦闘数

		public:
			
			EnemyManager() : dataManager_m()
			{
				initIdList();
			}
			~EnemyManager() {

			}
			using pic = std::shared_ptr<PictureObject>;
			void setObjects(pic enemy, pic background, std::shared_ptr<CutIn> cutIn)
			{
				backPic_m = background;
				cutIn_m = cutIn;
				enemyPic_m = enemy;
				initIdList();
			}
			void update()override {

				//マウス押しでフェードアウトの早さを調節
				BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

				switch (StateManager::getState())
				{

					//正解を選んだ瞬間の処理
				case BattleState::Corect:
					enemyPic_m->setFadeOut();
					enemyPic_m->setRoolAndSmall();
					break;

					// 時間切れになった瞬間の処理
				case BattleState::TimeOver:
					enemyPic_m->setExpansion();
					break;

				default:
					break;
				}
			}
			void draw()const override {
				/*enemyPic_m->draw();
				cutIn_m->draw();*/
			}
			std::shared_ptr<EnemyData> getEnemy() {
				return enemy_m;
			}

			int getId(int round) {
				return (0 < round && round < 31) ? enemyIdList_m[round] : 0;
			}

			void newEnemy(int round) {

				//int round = round;// round_m->getRound();

				// 次の敵のデータを取得
				enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(getId(round)));

				int id = enemy_m->id_m;

				// 特殊な処理をする敵の場合の関数を呼ぶ
				if (id == 16) { montagePhantom(round); }
				else if (id == 29) { carillon(); }

				// Enemy画像設定
				enemyPic_m->changeTexture(Format(L"Enemy", enemy_m->id_m));
				enemyPic_m->setBigger();

				// 背景画像設定
				backPic_m->changeTexture(Format(L"battleBack", enemy_m->bgid_m));

				// 正解を登録
				AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

				// 特殊な敵の時カットインを入れる	
				if (id == 16 || id == 22 || id == 29) { cutIn_m->init(); }
				else { cutIn_m->hide(); }
			}
		private:
			// 登場順リストを初期化する
			void initIdList() {
				for (int i = 1; i <= 30; i++)enemyIdList_m[i] = i;
				swap(enemyIdList_m[16], enemyIdList_m[27]);
				swap(enemyIdList_m[22], enemyIdList_m[28]);
				for (int i = 1; i <= 26; i++) {
					swap(enemyIdList_m[i], enemyIdList_m[Random(1, 26)]);
				}
				swap(enemyIdList_m[27], enemyIdList_m[Random(15, 29)]);
				swap(enemyIdList_m[28], enemyIdList_m[Random(15, 29)]);
				swap(enemyIdList_m[29], enemyIdList_m[Random(15, 29)]);
			}

			// 特殊モンスター　モンタージュファントム
			void montagePhantom(int round) {
				int rand;
				do {
					rand = enemyIdList_m[Random(1, round - 1)];
				} while (rand == 16 || rand == 22 || rand == 29);		//特殊モンスターはコピーしない

				//コピーするモンスターのデータを取得
				auto monta = make_shared<EnemyData>(dataManager_m.getEnemy(rand));

				//登場メッセージを設定
				enemy_m->messages_m.onContact_m = L"モンタージュファントムが現れた！\nモンタージュファントムは" + monta->name_m + L"に変化した！";

				//攻撃失敗時のメッセージを設定
				enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"に攻撃を仕掛けた！\nだが倒しきれなかった！";

				//正解をコピー
				enemy_m->collectAnswer_m = monta->collectAnswer_m;

				//選択肢をコピー
				for (int i = 0; i < 3; i++) {
					enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
					enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
					enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
				}
			}
			// 特殊モンスター　カリキョン
			void carillon() {

				//式と答えを設定
				int a = Random(10, 99);
				int b = Random(1, a);
				String ope = (Random(1) == 0) ? L"+" : L"-";
				int ans = (ope == L"+") ? a + b : a - b;

				//正解を設定
				enemy_m->collectAnswer_m = Format(ans);

				//登場メッセージを設定
				enemy_m->messages_m.onContact_m = Format(L"計算兵器カリキョンが現れた！\n「", a, ope, b, L"は？」");

				//攻撃失敗時のメッセージを設定
				enemy_m->messages_m.onPlayerLost_m = Format(L"「この程度の問題を間違えるな」\n計算兵器カリキョンを倒しきれなかった！");//\n「", a, ope, b, L"は？」");

				  //選択肢をランダムに用意
				int nums[9];
				for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
				nums[Random(8)] = ans + 10;		// 正解より10大きい選択肢を用意
				nums[Random(8)] = ans;			// 正解を用意

				for (int i = 0; i < 3; i++) {
					enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
					enemy_m->answers_m.magic_m[i] = Format(nums[3 + i]);
					enemy_m->answers_m.special_m[i] = Format(nums[6 + i]);
				}

			};
		};
	};

}
/***********************************************************************************************************************/

Battle::Battle(){};

Battle::~Battle(){};

void Battle::init(){
	TextureAsset::Register(L"logo", L"/201");

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
	objects.push_back(std::make_shared<SoundPlayer>());
	
	// 各種初期化
	AnswerManager::init();
	StateManager::init();

	// 戦闘数
	roundCounter_m = make_shared<RoundCounter>(Point(100, windowPosY ), L"miniMesWindow");
	addObject(roundCounter_m, 10);

	// メッセージ
	message_m = make_shared<MessageWindow>(Point(Window::Width() / 2, windowPosY), L"mesWindow");
	addObject(message_m, 10);

	// タイマー
	timer_m = make_shared<Timer>(Point(Window::Width() - 100,windowPosY ), L"miniMesWindow");
	addObject(timer_m, 10);

	// 回答のボタン
	answerButtons = make_shared<AnswerButtons>();
	addObject(answerButtons, 10);
	const int width = 420;
	const int height = 60;
	
	// タイトルボタン
	auto titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	addObject(titleButton, 12);
	ButtonManager::add(titleButton);

	// 次へボタン
	auto nextButton = make_shared<NextButton>(Point(Window::Width() / 2 - width / 2, Window::Height() - height * 4 - tx * 4), Size(width, height), L"battleButton");
	addObject(nextButton, 12);
	ButtonManager::add(nextButton);

	// 背景画像
	auto backPic_m = make_shared<PictureObject>(L"battleBack5",1.0,Window::Center());
	addObject(backPic_m, 1);

	// カットイン
	auto cutIn_m = make_shared<CutIn>();
	addObject(cutIn_m, 15);

	//enemyData
	auto enemyPic_m = make_shared<PictureObject>(L"logo", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemyPic_m, 5);

	enemyManger_m = make_shared<EnemyManager>();
	enemyManger_m->setObjects(enemyPic_m, backPic_m, cutIn_m);
	objects.push_back(enemyManger_m);
};

void Battle::update(){
	//ClearPrint();
	for_each(objects.begin(), objects.end(), [](auto obj) {obj->update(); });

	StateManager::update();	

	switch (StateManager::getState())
	{

		// ゲーム開始時
	case BattleState::Start:
		if (AnswerManager::checkAnswer() == Answers::correct) {
			StateManager::goToNext();
		}
		break;

		// 敵が登場するときの処理
	case BattleState::EnemyEntry:
		roundCounter_m->next();
		enemyManger_m->newEnemy(roundCounter_m->getRound());
		answerButtons->setAnswers(enemyManger_m->getEnemy());
		message_m->setEnemy(enemyManger_m->getEnemy());
		break;

		// 回答
	case BattleState::Answer:
		break;

		// 不正解を選んで選択できなくなっている間の処理
	case BattleState::CanNotAnswer:
		AnswerManager::init();
		break;

		// 不正解を選んだ瞬間の処理
	case BattleState::Incorect:
		//AnswerManager::init();
		break;

		//正解を選んだ瞬間の処理
	case BattleState::Corect:		
		break;

		// 正解して敵が消えていく間の処理
	case BattleState::ExitEnemy:
		break;

		// 時間切れになった瞬間の処理
	case BattleState::TimeOver:
		break;

		//// ゲームオーバーになった時の処理
	case BattleState::GameOver:
		break;

	case BattleState::CheckGameClear:
		if (roundCounter_m->isGameClear()){
			StateManager::setGameClear();
		}
		break;

	case BattleState::GoToResult:
		nextScene(L"Test");
		break;

	case BattleState::BackToTitle:
		nextScene(L"Title");
		break;

	default:
		break;
	
	}
};

void Battle::draw()const{
	drawList_m.drawAll();
};

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer) {
	objects.push_back(obj);
	drawList_m.add(obj, layer);
}

void Battle::nextScene(String sceneName) {
	DataManager dataManager_m;

	m_data->time = timer_m->getTime();
	for (int i = 1; i < roundCounter_m->getRound(); i++) {
		m_data->addEnemy(enemyManger_m->getId(i));
		dataManager_m.setSaveData(enemyManger_m->getId(i), true);
	}
	dataManager_m.writeSaveData();
	changeScene(sceneName);
}
