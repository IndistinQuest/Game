#include"Battle.h"

#include"..\..\Drawable\Drawable.h"

#include"..\..\Button\BasicButton.h"
#include"../../Button/ButtonManager.h"

#include"../../Data/DataManager.h"
#include"..\..\Data\EnemyData.h"

#include"..\..\TextView\TextView.h"

using namespace std;

namespace scene {
	namespace battle {
		
		// �l��ݒ�
		namespace BattleSceneNums {

			// �������Ԃ̏����l
			const int timeLimit = 30000;

			// �����������̐������Ԃ̑�����
			const int timeRecovery = 9000;

			// Enemy�摜�̊g�嗦
			const double scale = 0.4;

			// Enemy�̃t�F�[�h�C��/�A�E�g�̑���
			const double fadeIn = 6;
			double fadeOut = 2;

			// �s�k����Enemy�̍ő�g�嗦
			const double maxScale = 2.0;

			// �s�k���̃��b�Z�[�W
			const String loseMessage = L"�ɂ��ꂽ�I";

			const String StartMes = L"�����͂����ł���?\nStart�������ƃQ�[�����n�܂�܂�!";

			// �ԈႦ�����{�^���������Ȃ��Ȃ鎞��
			const int penaltyTime = 120;
		}

		// ���
		enum class BattleState { Start, EnemyEntry, Answer, CanNotAnswer, Incorect, Corect, ExitEnemy, TimeOver, GameOver, BackToTitle, GoToResult, CheckGameClear };

		// �A���T�[�}�l�[�W��
		enum Answers { correct, incorrect, not };
		class AnswerManager {
		private:
			static String corectAnswer;
			static Answers playersAnswer;
			static bool isAnswered;
		public:
			static void init() {
				isAnswered = false;
			};
			static void setCorectAnswer(String corect) {
				corectAnswer = corect;
				isAnswered = false;
			};
			static void answer(String ans) {
				playersAnswer = (ans == corectAnswer) ? Answers::correct : Answers::incorrect;
				isAnswered = true;
			};
			static Answers checkAnswer() {
				if (isAnswered == false) { playersAnswer = Answers::not; }
				return playersAnswer;
			};
		};
		String AnswerManager::corectAnswer = L"";
		Answers AnswerManager::playersAnswer = Answers::not;
		bool AnswerManager::isAnswered = false;

		// �X�e�[�g�}�l�[�W��
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
				if (AnswerManager::checkAnswer() == Answers::correct) {
					StateManager::goToNext();
				}
				if (isImprove) {
					curentState_m = BattleState::EnemyEntry;
				}
				break;

				// �G���o�ꂷ��Ƃ��̏���
			case BattleState::EnemyEntry:
				curentState_m = BattleState::Answer;
				break;

				// ��
			case BattleState::Answer:
			{
				auto ans = AnswerManager::checkAnswer();
				// ������
				if (ans == Answers::correct) {
					curentState_m = BattleState::Corect;
				}
				// �s������
				else if (ans == Answers::incorrect) {
					curentState_m = BattleState::Incorect;
				}
			}
			break;

			// �s������I��őI���ł��Ȃ��Ȃ��Ă���Ԃ̏���
			case BattleState::CanNotAnswer:
				if (isImprove) {
					curentState_m = BattleState::Answer;
				}				
				AnswerManager::init();
				break;

				// �s������I�񂾏u�Ԃ̏���
			case BattleState::Incorect:
				curentState_m = BattleState::CanNotAnswer;				
				break;

				//������I�񂾏u�Ԃ̏���
			case BattleState::Corect:
				curentState_m = BattleState::ExitEnemy;
				break;

				// �������ēG�������Ă����Ԃ̏���
			case BattleState::ExitEnemy:
				if (StateManager::isImprove) {
					curentState_m = BattleState::CheckGameClear;
				}
				break;

			case BattleState::CheckGameClear:
				curentState_m = BattleState::EnemyEntry;
				break;

				// ���Ԑ؂�ɂȂ����u�Ԃ̏���
			case BattleState::TimeOver:
				curentState_m = BattleState::GameOver;
				break;

				// �Q�[���I�[�o�[�ɂȂ������̏���
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

		// ���N���X
		class BattleSceneObject : public Drawable
		{
		public:
			virtual void update() = 0;
		};

		//�e�L�X�g�t���E�B���h�E
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

		// �^�C�}�[
		class Timer : public WindowAndText {
		private:
			int time_m;
			//int TIME_RECOVERY;
			//Milliseconds time_m;
			std::shared_ptr<GameData> data_m;
			Stopwatch stopWatch_m;
		public:
			Timer(Point center, String textureAssetName, Color c = Palette::Black) 
				:WindowAndText(center, textureAssetName, c)
				//, TIME_RECOVERY(BattleSceneNums::timeRecovery)
			{
				
				time_m = BattleSceneNums::timeLimit;
				//setText(Format(Pad(time_m / 1000, { 2,L'0' }), L".", Pad(time_m % 1000, { 3,L'0' })));
				stopWatch_m.reset();
				timeShow();			
			}
			~Timer() {
				data_m->time = Max(0, time_m - stopWatch_m.ms() );
			}
			void update() override {
				int curentTime = getCurentTime();
				strColor_m = ((curentTime < 10000) ? Palette::Red : Palette::Black);
				for (int i = 0; i < 4; i++) { SoundAsset(Format(L"battle_bgm",i)).changeTempo((curentTime < 10000) ? 1.2 : 1.0); }
				switch (StateManager::getState()) {
				case BattleState::Answer:
				case BattleState::CanNotAnswer:
					//time_m--;
				{
					stopWatch_m.start();					
					if (curentTime <= 0) { StateManager::setTimeOver(); }
		
					break;
				}
				case BattleState::Corect:
					recovery();
					break;
				default:
					stopWatch_m.pause();
					break;

				}
				timeShow();
				
			}
			void recovery() {
				//time_m += TIME_RECOVERY;
				//stopWatch_m.set(static_cast<Milliseconds>(stopWatch_m.ms() + 7000) );
				time_m += BattleSceneNums::timeRecovery;
			}
			void setGameData(std::shared_ptr<GameData> data) {
				data_m = data;
			}
			void timeShow(){
				int curentTime = getCurentTime();
				setText(Format(Pad(curentTime / 1000, { 2,L'0' }), L".", Pad((curentTime % 1000)/10, { 2,L'0' })));
			}
			int getCurentTime() {
				return Max(0, time_m - stopWatch_m.ms());
			}

			//int getTime() {
			//	//return time_m;
			//	return stopWatch_m.ms();
			//}
		};

		// �퓬��
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
				setText(Format(round_m, L"���"));
			}
			void update()override {
				// �G���o�ꂷ��Ƃ��̏���
				switch (StateManager::getState()) {
				case BattleState::EnemyEntry:
					next();
					break;
				case BattleState::CheckGameClear:					
					if (isGameClear()) {
						round_m++;
						StateManager::setGameClear();
					}
					break;
				default:
					break;					
				}
			}
			bool isGameClear() {
				return round_m >= 30;
			}
			int getRound() {
				return round_m;
			}
		};

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
			// �V�����摜�ɕς���
			// String text �摜�̖��O
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

		// �J�b�g�C��
		class CutIn : public BattleSceneObject
		{
		private:
			const Point END_POS = { 155,200 };
			const double LAST_SCALE = 0.5;
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
					if (scale_m > LAST_SCALE) {
						scale_m -= 0.3;
					}
					else {
						scale_m = LAST_SCALE;
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

		// �G�l�~�[�}�l�[�W��
		class EnemyManager : public BattleSceneObject {
		private:
			std::shared_ptr<EnemyData> enemy_m;				// Enemy�f�[�^
			DataManager dataManager_m;						// �f�[�^�}�l�[�W��
			int enemyIdList_m[31];							// �o�ꏇ���X�g
			std::shared_ptr<GameData> data_m;				// �Q�[���f�[�^

			std::shared_ptr<PictureObject> enemyPic_m;		// Enemy�摜
			std::shared_ptr<CutIn> cutIn_m;					// �J�b�g�C��
			std::shared_ptr<PictureObject> backPic_m;		// �w�i�摜
			std::shared_ptr<RoundCounter> round_m;			// �퓬��

		public:
			EnemyManager() : dataManager_m()
			{
				initIdList();
			}
			~EnemyManager() {
				writeGameDataAndSaveData(data_m);
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

				//�}�E�X�����Ńt�F�[�h�A�E�g�̑����𒲐�
				BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

				switch (StateManager::getState())
				{
					// �G���o�ꂷ��Ƃ��̏���
				case BattleState::EnemyEntry:
					newEnemy();
					break;
					//������I�񂾏u�Ԃ̏���
				case BattleState::Corect:
					enemyPic_m->setFadeOut();
					enemyPic_m->setRoolAndSmall();
					break;

					// ���Ԑ؂�ɂȂ����u�Ԃ̏���
				case BattleState::TimeOver:
					enemyPic_m->setExpansion();
					break;

				default:
					break;
				}
			}

			void draw()const override {}

			std::shared_ptr<EnemyData> getEnemy() {
				return enemy_m;
			}

			int getId(int round) {
				return (0 < round && round < 31) ? enemyIdList_m[round] : 0;
			}

			void setRoundCounter(std::shared_ptr<RoundCounter> r) {
				round_m = r;
			}

			void setGameData(std::shared_ptr<GameData> data) {
				data_m = data;
			}

			void newEnemy() {

				int round = round_m->getRound();

				// ���̓G�̃f�[�^���擾
				enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(getId(round)));

				int id = enemy_m->id_m;

				// ����ȏ���������G�̏ꍇ�̊֐����Ă�
				if (id == 16) { montagePhantom(round); }
				else if (id == 29) { carillon(); }

				// Enemy�摜�ݒ�
				enemyPic_m->changeTexture(Format(L"Enemy", enemy_m->id_m));
				enemyPic_m->setBigger();

				// �w�i�摜�ݒ�
				backPic_m->changeTexture(Format(L"battleBack", enemy_m->bgid_m));

				// ������o�^
				AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

				// ����ȓG�̎��J�b�g�C��������	
				if (id == 16 || id == 22 || id == 29) { cutIn_m->init(); }
				else { cutIn_m->hide(); }
			}

			void writeGameDataAndSaveData(std::shared_ptr<GameData> data) {
				for (int i = 1; i < round_m->getRound(); i++) {
					data->addEnemy(getId(i));
					dataManager_m.setSaveData(getId(i), true);
				}
				dataManager_m.writeSaveData();
			}

		private:
			// �o�ꏇ���X�g������������
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

			// ���ꃂ���X�^�[�@�����^�[�W���t�@���g��
			void montagePhantom(int round) {
				int rand;
				do {
					rand = enemyIdList_m[Random(1, round - 1)];
				} while (rand == 16 || rand == 22 || rand == 29);		//���ꃂ���X�^�[�̓R�s�[���Ȃ�

				//�R�s�[���郂���X�^�[�̃f�[�^���擾
				auto monta = make_shared<EnemyData>(dataManager_m.getEnemy(rand));

				//�o�ꃁ�b�Z�[�W��ݒ�
				enemy_m->messages_m.onContact_m = L"�����^�[�W���t�@���g�������ꂽ�I\n�����^�[�W���t�@���g����" + monta->name_m + L"�ɕω������I";

				//�U�����s���̃��b�Z�[�W��ݒ�
				enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"�ɍU�����d�|�����I\n�����|������Ȃ������I";

				//�������R�s�[
				enemy_m->collectAnswer_m = monta->collectAnswer_m;

				//�I�������R�s�[
				for (int i = 0; i < 3; i++) {
					enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
					enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
					enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
				}
			}
			// ���ꃂ���X�^�[�@�J���L����
			void carillon() {

				//���Ɠ�����ݒ�
				int a = Random(10, 99);
				int b = Random(1, a);
				String ope = (Random(1) == 0) ? L"+" : L"-";
				int ans = (ope == L"+") ? a + b : a - b;

				//������ݒ�
				enemy_m->collectAnswer_m = Format(ans);

				//�o�ꃁ�b�Z�[�W��ݒ�
				enemy_m->messages_m.onContact_m = Format(L"�v�Z����J���L���������ꂽ�I\n�u", a, ope, b, L"�́H�v");

				//�U�����s���̃��b�Z�[�W��ݒ�
				enemy_m->messages_m.onPlayerLost_m = Format(L"�u���̒��x�̖����ԈႦ��ȁv\n�v�Z����J���L������|������Ȃ������I");//\n�u", a, ope, b, L"�́H�v");

				//�I�����������_���ɗp��
				int nums[9];
				for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
				nums[Random(8)] = ans + 10;		// �������10�傫���I������p��
				nums[Random(8)] = ans;			// ������p��

				for (int i = 0; i < 3; i++) {
					enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
					enemy_m->answers_m.magic_m[i] = Format(nums[3 + i]);
					enemy_m->answers_m.special_m[i] = Format(nums[6 + i]);
				}

			};
		};

		//���b�Z�[�W
		class MessageWindow : public WindowAndText, public TextView {
		private:
			std::shared_ptr<EnemyManager> enemyManager_m;
			bool incorect_m;
		public:
			MessageWindow(Point center, String textureAssetName, Color c = Palette::Black)
				: WindowAndText(center, textureAssetName, c)
				, TextView(L"", Point(210, center.y - 60), 850, 3, Font(20), 1, Palette::Black) {
				setNewText(BattleSceneNums::StartMes);
				incorect_m = false;
			}
			void update()override {
				//setIntervalIncrease((Input::MouseL.pressed) ? 0 : 3); //���b�Z�[�W���x�ύX

				switch (StateManager::getState())
				{
				case BattleState::Answer:
					if (incorect_m && isAllPoltAndOverTime()) {
						setNewText(enemyManager_m->getEnemy()->messages_m.onContact_m);
						incorect_m = false;
					}
					break;
				case BattleState::EnemyEntry:
					setNewText(enemyManager_m->getEnemy()->messages_m.onContact_m);
					incorect_m = false;
					break;
				case BattleState::TimeOver:
					setNewText(enemyManager_m->getEnemy()->name_m + BattleSceneNums::loseMessage);
					break;
				case BattleState::Corect:
					setNewText(enemyManager_m->getEnemy()->messages_m.onPlayerWon_m);
					break;
				case BattleState::Incorect:
					setNewText(enemyManager_m->getEnemy()->messages_m.onPlayerLost_m);
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
			void setEnemyManager(std::shared_ptr<EnemyManager> e) {
				enemyManager_m = e;
			}
		};

		//�{�^��
		class BattleSceneButton : public BasicButton, public BattleSceneObject {
		protected:
			const Size size;
			const Point pos;
			const Point center;
			String text_m;
			const String textureAssetName_m;
			Color color_m;	//�����F
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
			void onClicked() = 0;
			void update()override {}
			void setStrColor(Color c) {
				color_m = c;
			}
		};

		// �񓚂̃{�^��
		class AnswerButton : public BattleSceneButton {
		public:
			AnswerButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {};
			void onClicked()override {
				AnswerManager::answer(text_m);
			}
		};

		// �^�C�g���ւ̃{�^��
		class TitleButton : public BattleSceneButton {
		public:
			TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {
				setText(L"�^�C�g���ɂ��ǂ�");
			};
			void onClicked() override {
				StateManager::setBackToTitle();
			}
		};

		// ���֐i�ރ{�^��
		class NextButton
			: public BattleSceneButton {
		public:
			NextButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black) :BattleSceneButton(pos, size, textureAssetName, c) {
				setText(L"���ɂ�����");
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

		// �񓚂̃{�^���S
		class AnswerButtons : public BattleSceneObject {
		private:
			std::shared_ptr<EnemyManager> enemyManager_m;
			std::shared_ptr<AnswerButton> buttons_m[9];
			int penalty_m;
		public:
			AnswerButtons() {
				const int tx = 5, ty = 5;
				const int width = 420;
				const int height = 60;
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
					// �G���o�ꂷ��Ƃ��̏���
				case BattleState::EnemyEntry:
					setAnswers();					
					break;

				case BattleState::Answer:
					for (auto& b : buttons_m) { b->setStrColor(Palette::Black); }
					break;

					// �s������I��őI���ł��Ȃ��Ȃ��Ă���Ԃ̏���
				case BattleState::CanNotAnswer:
					penalty_m--;
					if (penalty_m == 0) {
						for (auto& b : buttons_m) { b->setStrColor(Palette::Black); }
						StateManager::goToNext();
					}
					break;

					// �s������I�񂾏u�Ԃ̏���
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
			void setAnswers() {
				// �{�^���ɑI������ݒ�
				for (int i = 0; i < 3; i++) {					
					buttons_m[i]->setText(enemyManager_m->getEnemy()->answers_m.weapon_m[i]);
					buttons_m[i + 3]->setText(enemyManager_m->getEnemy()->answers_m.magic_m[i]);
					buttons_m[i + 6]->setText(enemyManager_m->getEnemy()->answers_m.special_m[i]);
				}
			}
			void setEnemyManager(std::shared_ptr<EnemyManager> e) {
				enemyManager_m = e;
			}
		};

		// �T�E���h
		class SoundPlayer : public BattleSceneObject {
			/*struct Pare {
				String name;
				double volume;
				Pare(String n) :name(n), volume(1.0) {};
			};
			std::vector<Pare> volumes;*/
			String bgmName_m;
		public:
			SoundPlayer() {
				// BGM�����[�v�Đ�

				bgmName_m = Format(L"battle_bgm", Random<int>(3));

				SoundAsset(bgmName_m).setLoop(true);
				SoundAsset(bgmName_m).play();

				SoundAsset(L"battle_corect").setVolume(1.0);
				SoundAsset(L"battle_incorect").setVolume(0.7);
				SoundAsset(L"battle_enter").setVolume(0.9);
				SoundAsset(L"battle_GameOver").setVolume(0.7);
				SoundAsset(bgmName_m).setVolume(0.7);
				
				/*volumes.push_back(Pare(L"battle_corect"));			
				volumes.push_back(Pare(L"battle_incorect"));
				volumes.push_back(Pare(L"battle_enter"));
				volumes.push_back(Pare(L"battle_GameOver"));
				volumes.push_back(Pare(L"battle_bgm"));*/
			}
			~SoundPlayer() {
				SoundAsset(bgmName_m).stop();
			}
			void update()override {				
				
				/*********************************************************************************************/
				// ��ŏ���
				/*volumes[0].volume += (Input::KeyQ.clicked - Input::KeyA.clicked)*0.1;
				volumes[1].volume += (Input::KeyW.clicked - Input::KeyS.clicked)*0.1;
				volumes[2].volume += (Input::KeyE.clicked - Input::KeyD.clicked)*0.1;
				volumes[3].volume += (Input::KeyR.clicked - Input::KeyF.clicked)*0.1;
				volumes[4].volume += (Input::KeyT.clicked - Input::KeyG.clicked)*0.1;
				MasterVoice::SetVolume(MasterVoice::GetVolume() + (Input::KeyY.clicked - Input::KeyH.clicked)*0.1);
				Println(L"Master : ",MasterVoice::GetVolume());
				for (int i = 0; i < volumes.size(); i++) {
					Clamp(volumes[i].volume, 0.0, 1.0);
					Println(volumes[i].name, L" : ", volumes[i].volume);
					SoundAsset(volumes[i].name).setVolume(volumes[i].volume);
				}*/
				/*************************************************************************************************/

				switch (StateManager::getState())
				{
					// �G���o�ꂷ��Ƃ��̏���
				case BattleState::EnemyEntry:
					// �G�o�ꎞ�̌��ʉ��Đ�
					SoundAsset(L"bettle_entry").setSpeed(0.5);
					SoundAsset(L"bettle_entry").play();
					break;

					// �s������I�񂾏u�Ԃ̏���
				case BattleState::Incorect:

					SoundAsset(L"battle_incorect").playMulti();
					break;

					//������I�񂾏u�Ԃ̏���
				case BattleState::Corect:
					SoundAsset(L"battle_corect").playMulti();
					break;

					// ���Ԑ؂�ɂȂ����u�Ԃ̏���
				case BattleState::TimeOver:
					SoundAsset(L"bettle_GameOver").play();
				default:
					break;
				}
			}
			void draw()const override {}
		};

	};

}

using namespace scene;
using namespace battle;

Battle::Battle(){};

Battle::~Battle(){};

void Battle::init(){

	//�e��萔
	const int tx = 5;
	const int ty = 5;	
	const int windowPosY = 80;
	const int width = 420;			//�{�^����
	const int height = 60;			//�ڂ����

	// �w�i�F�ύX
	Graphics::SetBackground(Palette::Lightslategray);

	// �{�^���}�l�[�W���̃N���A
	ButtonManager::clearAll();
	ButtonManager::update();

	// GameData ������
	m_data->resetEnemyList();
	m_data->time = 0;

	// �e�평����
	AnswerManager::init();
	StateManager::init();

	// BGM�Đ�
	addObject(std::make_shared<SoundPlayer>());	

	// �퓬��
	auto roundCounter = make_shared<RoundCounter>(Point(100, windowPosY ), L"miniMesWindow");
	addObject(roundCounter, 10,1);

	// �^�C�}�[
	auto timer = make_shared<Timer>(Point(Window::Width() - 100, windowPosY), L"miniMesWindow");
	timer->setGameData(m_data);
	addObject(timer, 10);

	// �w�i�摜
	auto backPic = make_shared<PictureObject>(L"battleBack5", 1.0, Window::Center());
	addObject(backPic, 1);

	// �J�b�g�C��
	auto cutIn = make_shared<CutIn>();
	addObject(cutIn, 15);

	// �G�l�~�[�摜
	auto enemyPic = make_shared<PictureObject>(L"title_logo2M", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemyPic, 5);

	// �G�l�~�[�}�l�[�W��
	auto enemyManger = make_shared<EnemyManager>();
	enemyManger->setRoundCounter(roundCounter);
	enemyManger->setGameData(m_data);
	enemyManger->setObjects(enemyPic, backPic, cutIn);
	addObject(enemyManger, 0, 2);

	// ���b�Z�[�W
	auto message = make_shared<MessageWindow>(Point(Window::Width() / 2, windowPosY), L"mesWindow");
	message->setEnemyManager(enemyManger);
	addObject(message, 10,3);

	// �񓚂̃{�^��
	auto answerButtons = make_shared<AnswerButtons>();
	answerButtons->setEnemyManager(enemyManger);
	addObject(answerButtons, 10,3);
	
	// �^�C�g���{�^��
	auto titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	addObject(titleButton, 12);
	ButtonManager::add(titleButton);

	// ���փ{�^��
	auto nextButton = make_shared<NextButton>(Point(Window::Width() / 2 - width / 2, Window::Height() - height * 4 - tx * 4), Size(width, height), L"battleButton");
	addObject(nextButton, 12);
	ButtonManager::add(nextButton);	
};

void Battle::update(){

	ClearPrint();
	
	for_each(objects.begin(), objects.end(), [](auto obj) { obj.second->update(); });

	StateManager::update();	

	switch (StateManager::getState())
	{
	case BattleState::GoToResult:
		changeScene(L"Result");
		break;

	case BattleState::BackToTitle:
		changeScene(L"Title");
		break;

	default:
		break;
	}
};

void Battle::draw()const{
	drawList_m.drawAll();
};

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj) {
	objects.insert(std::make_pair(4, obj));
}

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer) {
	addObject(obj, layer, 4);
}

void Battle::addObject(std::shared_ptr<BattleSceneObject> obj, int layer,const int order) {
	objects.insert(std::make_pair(order,obj));
	drawList_m.add(obj, layer);
}
