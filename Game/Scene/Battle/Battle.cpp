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

// �l��ݒ�
namespace BattleSceneNums {

	// �������Ԃ̏����l
	const int timeLimit = 1800;

	// �����������̐������Ԃ̑�����
	const int timeRecovery = 420;

	// Enemy�摜�̊g�嗦
	const double scale = 0.4;

	// Enemy�̃t�F�[�h�C��/�A�E�g�̑���
	const double fadeIn = 6;
	double fadeOut = 2;

	// �s�k����Enemy�̍ő�g�嗦
	const double maxScale = 2.0;

	// ���̃V�[��
	const String nextScene = L"Result";

	// �s�k���̃��b�Z�[�W
	const String loseMessage = L"�ɂ��ꂽ�I\n�N���b�N�Ŏ��ւ�����...";

	// ���b�Z�[�W�\�����x
	const int mesSpeed = 2;

	// �ԈႦ�����{�^���������Ȃ��Ȃ鎞��
	const int penaltyTime = 60;
}

//��
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

// ���N���X
class BattleSceneObject : public Drawable
{
public:
	virtual void update() = 0;
	virtual void setText(String text) = 0;
};

//�E�B���h�E
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

//�{�^��
class BattleSceneButton : public BasicButton , public BattleSceneObject{
private:
	const Size size;
	const Point pos;
	const Point center;
	String text_m;
	const String textureAssetName_m;
	Color color_m;	//�����F
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

class TitleButton : public BattleSceneButton {
public:
	TitleButton(Point pos, Size size, String textureAssetName, Color c = Palette::Black):BattleSceneButton(pos,size,textureAssetName,c) {};
	void onClicked() override{
		isGoTitle = true;
	}
};

//�摜
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
	// �V�����摜�ɕς���
	// String text �摜�̖��O
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

}
}

/***********************************************************************************************************************/

Battle::Battle() {};

Battle::~Battle(){};

void Battle::init(){
	//�e��萔
	const String assetPath = L"Asset/";
	const int tx = 5;
	const int ty = 5;	

	// �w�i�F�ύX
	Graphics::SetBackground(Palette::Lightslategray);

	// �{�^���}�l�[�W���̃N���A
	ButtonManager::clearAll();
	ButtonManager::update();

	// GameData ������
	m_data->resetEnemyList();
	m_data->time = 0;

	// �t�H���g�A�Z�b�g�o�^
	//if (!FontAsset::IsRegistered(L"CommandFont")) {	FontAsset::Register(L"CommandFont", 20);}
	if (!FontAsset::IsRegistered(L"BattleSceneFont")) {	FontAsset::Register(L"BattleSceneFont", 20);}

	// �e�N�X�`���A�Z�b�g�o�^
	if (!TextureAsset::IsRegistered(L"mesWindow")) { TextureAsset::Register(L"mesWindow", L"/501"); }
	if (!TextureAsset::IsRegistered(L"miniMesWindow")) { TextureAsset::Register(L"miniMesWindow", L"/502"); }
	if (!TextureAsset::IsRegistered(L"battleButton")) { TextureAsset::Register(L"battleButton", L"/500"); }
	if (!TextureAsset::IsRegistered(L"CutInEffect")) { TextureAsset::Register(L"CutInEffect", L"/503"); }
	for (int i = 1; i <= 5; i++) {
		TextureAsset::Register(Format(L"battleBack",i), Format(L"/",(510 + i)));
	}	

	// �T�E���h�A�Z�b�g�o�^
	SoundAsset::Register(L"battle_corect", L"/521");
	SoundAsset::Register(L"battle_incorect", L"/522");
	SoundAsset::Register(L"battle_bgm", L"/520");
	SoundAsset::Register(L"bettle_GameOver", L"/523");
	SoundAsset::Register(L"bettle_entry", L"/524");

	// BGM�Đ�
	SoundAsset(L"battle_bgm").setLoop(true);
	SoundAsset(L"battle_bgm").play();
	
	// �e�평����
	round_m = 0;
	time_m = BattleSceneNums::timeLimit;
	state_m = BattleState::start;
	AnswerManager::init();
	isGoTitle = false;
	incorect = false;

	// Window
	const int windowPosY = 80;
	auto r = WindowAndText({ 100,windowPosY }, L"miniMesWindow");
	r.setText(L"0���");
	addObject(make_shared<WindowAndText>(r), L"RoundWindow", 10);
	auto m = WindowAndText({ Window::Width() / 2,windowPosY }, L"mesWindow");
	addObject(make_shared<WindowAndText>(m), L"messageWindow", 10);
	auto t = WindowAndText({ Window::Width() - 100,windowPosY }, L"miniMesWindow");
	t.setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m % 60, { 2, L'0' })));
	addObject(make_shared<WindowAndText>(t), L"timeWindow", 10);

	// message
	message_m = make_shared<TextView>(L"�����͂����ł���?\nStart�������ƃQ�[�����n�܂�܂�!", Point(210,windowPosY-60) , 850, 3, Font(20), BattleSceneNums::mesSpeed, Palette::Black);
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
			b->setText(L"Start");
			CommantButton_m[3*i+j] = b;
			ButtonManager::add(b);
			addObject(b, Format(buttonName[i],j), 10);
		}
	}
	AnswerManager::setCorectAnswer(L"Start");

	titleButton = make_shared<TitleButton>(TitleButton({ Window::Width() / 2 - width / 2 + (width + tx), windowPosY*2 + ty }, Size(width, height), L"battleButton"));
	titleButton->setText(L"�^�C�g���ɂ��ǂ�");
	addObject(titleButton,L"titleButton", 12);
	ButtonManager::add(titleButton);

	// �w�i�摜
	backPic_m = make_shared<PictureObject>(L"battleBack5",1.0,Window::Center());
	addObject(backPic_m, L"background", 1);

	// �J�b�g�C��
	cutIn_m = make_shared<CutIn>();
	addObject(cutIn_m, L"CutIn", 15);

	// Enemy ID List
	// 16 22 29 30������
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
	TextureAsset::Register(L"logo", L"/201");
	enemyPic_m = make_shared<PictureObject>(L"logo", BattleSceneNums::scale, Point(Window::Width() / 2, 330));
	addObject(enemyPic_m, L"enemy",5);

	
	//newEnemy();
};

void Battle::update(){
	ClearPrint();
	for_each(objects.begin(), objects.end(), [](auto pare) {pare.second->update(); });
	message_m->update();

	if (isGoTitle) { nextScene(L"Title"); }

	//���b�Z�[�W���x�ύX
	message_m->setIntervalIncrease((Input::MouseL.pressed) ? 0 : 3);

	// �t�F�[�h�A�E�g���x�ύX
	BattleSceneNums::fadeOut = (Input::MouseL.pressed) ? 4 : 2;

	switch (state_m)
	{
	case BattleState::start:
	{
		auto ans = AnswerManager::checkAnswer();
		if (ans == Answers::correct) {
			state_m = BattleState::select;
			canAnswer = false;
			round_m++;
			objects.find(L"RoundWindow")->second->setText(Format(round_m, L"���"));
			newEnemy();

			canAnswer = true;
		}
	}
	break;
	case BattleState::select:
			// �^�C�}�[
		{
			time_m--;
			objects.find(L"timeWindow")->second->setText(Format(Pad(time_m / 60, { 2, L'0' }), L".", Pad(time_m % 60, { 2, L'0' })));
			if (time_m <= 0) {
				state_m = BattleState::lose;
				SoundAsset(L"bettle_GameOver").play();
				message_m->setNewText(enemy_m->name_m + BattleSceneNums::loseMessage);
				enemyPic_m->setExpansion();
			}
			SoundAsset(L"battle_bgm").changeTempo((time_m < 300) ? 1.5 : 1.0);

		}
		// ��
		{
			auto ans = AnswerManager::checkAnswer();

			// �{�^���̌듮��h�~
			if (!canAnswer) {
				if (Input::MouseL.released) {
					canAnswer = true;
				}
				AnswerManager::init();				
				break;
			}
			
			// �y�i���e�B
			if (penalty_m > 0) {
				penalty_m--;				
				if (penalty_m == 0) {
					for (auto& b : CommantButton_m) { b->setStrColor(Palette::Black); }
					AnswerManager::init();
				}
				break;
			}

			// ������
			if (ans == Answers::correct) {
				state_m = BattleState::win;
				message_m->setNewText(enemy_m->messages_m.onPlayerWon_m);
				enemyPic_m->setFadeOut();
				enemyPic_m->setRoolAndSmall();
				//backPic_m->setFadeOut();

				time_m += BattleSceneNums::timeRecovery;

				dataManager_m.setSaveData(enemy_m->id_m, true);
				m_data->addEnemy(enemy_m->id_m);
				
				SoundAsset(L"battle_corect").playMulti();
			}
			// �s������
			else if (ans == Answers::incorrect) {
				message_m->setNewText(enemy_m->messages_m.onPlayerLost_m);
				AnswerManager::init();
				SoundAsset(L"battle_incorect").playMulti();
				incorect = true;

				penalty_m = BattleSceneNums::penaltyTime;
				for (auto& b : CommantButton_m) { b->setStrColor(Palette::Red); }
			}
		}		
		if (incorect && message_m->isAllPoltAndOverTime()) {
			message_m->setNewText(enemy_m->messages_m.onContact_m);
			incorect = false;		
		}
		break;
	// ������
	case BattleState::win:
		if (message_m->isPlotAll() && !enemyPic_m->isDraw() && Input::MouseL.pressed ) {
			incorect = false;
			if (round_m == 30) {
				nextScene(BattleSceneNums::nextScene);
			}
			else {				
				state_m = BattleState::select;
				canAnswer = false;
				round_m++;
				objects.find(L"RoundWindow")->second->setText(Format(round_m, L"���"));
				newEnemy();				
			}
		}
		break;

	// GameOver
	case BattleState::lose:		
		if (message_m->isPlotAll() && Input::MouseL.pressed ) {
			nextScene(BattleSceneNums::nextScene);
		}		
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
	m_data->time = time_m;
	dataManager_m.writeSaveData();
	SoundAsset(L"battle_bgm").stop();
	changeScene(sceneName);
}

void Battle::newEnemy() {

	// ���̓G�̃f�[�^���擾
	enemy_m = make_shared<EnemyData>(dataManager_m.getEnemy(enemy_ID_List_m[round_m]));

	int id = enemy_m->id_m;

	// ���ꃂ���X�^�[�@�����^�[�W���t�@���g��
	if (id == 16) {
		int rand;
		do {		
			rand = RandomSelect(m_data->defeatedEnemyList);
		} while (rand == 16 || rand == 22 || rand == 29);		//���ꃂ���X�^�[�̓R�s�[���Ȃ�

		// �R�s�[���郂���X�^�[�̃f�[�^���擾
		auto monta = make_shared<EnemyData>(dataManager_m.getEnemy(rand));

		// �o�ꃁ�b�Z�[�W��ݒ�
		enemy_m->messages_m.onContact_m = L"�����^�[�W���t�@���g�������ꂽ�I\n�����^�[�W���t�@���g����" + monta->name_m + L"�ɕω������I";

		// �U�����s���̃��b�Z�[�W��ݒ�
		enemy_m->messages_m.onPlayerLost_m = monta->name_m + L"�ɍU�����d�|�����I\n�����|������Ȃ������I";

		// �������R�s�[
		enemy_m->collectAnswer_m = monta->collectAnswer_m;

		// �I�������R�s�[
		for (int i = 0; i < 3; i++) {
			enemy_m->answers_m.weapon_m[i] = monta->answers_m.weapon_m[i];
			enemy_m->answers_m.magic_m[i] = monta->answers_m.magic_m[i];
			enemy_m->answers_m.special_m[i] = monta->answers_m.special_m[i];
		}
	}

	// ���ꃂ���X�^�[�@�J���L����
	else if (id == 29) {
		
		// ���Ɠ�����ݒ�
		int a = Random(10,99);
		int b = Random(1,a);
		String ope = (Random(1) == 0) ? L"+" : L"-";
		int ans = (ope == L"+") ? a + b : a - b;

		// ������ݒ�
		enemy_m->collectAnswer_m = Format(ans);

		// �o�ꃁ�b�Z�[�W��ݒ�
		enemy_m->messages_m.onContact_m = Format(L"�v�Z����J���L���������ꂽ�I\n�u",a,ope,b,L"�́H�v");

		// �U�����s���̃��b�Z�[�W��ݒ�
		enemy_m->messages_m.onPlayerLost_m = Format(L"�u���̒��x�̖����ԈႦ��ȁv\n�v�Z����J���L������|������Ȃ������I");//\n�u", a, ope, b, L"�́H�v");

		// �I�����������_���ɗp��
		int nums[9];
		for (int i = 0; i < 9; i++) nums[i] = Random(1, 100);
		nums[Random(8)] = ans + 10;		// �������10�傫���I������p��
		nums[Random(8)] = ans;			// ������p��
		
		for (int i = 0; i < 3; i++) {
			enemy_m->answers_m.weapon_m[i] = Format(nums[i]);
			enemy_m->answers_m.magic_m[i] = Format(nums[3+i]);
			enemy_m->answers_m.special_m[i] = Format(nums[6+i]);
		}
	}

	// Enemy�摜�ݒ�
	enemyPic_m->setText(Format(L"Enemy",enemy_m->id_m));
	enemyPic_m->setBigger();

	// �w�i�摜�ݒ�
	backPic_m->setText(Format(L"battleBack", enemy_m->bgid_m));	

	// ������o�^
	AnswerManager::setCorectAnswer(enemy_m->collectAnswer_m);

	// �o�ꃁ�b�Z�[�W��ݒ�
	message_m->setNewText(enemy_m->messages_m.onContact_m);

	// �{�^���ɑI������ݒ�
	for (int i = 0; i < 3; i++) {
		objects.find(Format(L"weapon", i))->second->setText(enemy_m->answers_m.weapon_m[i]);
		objects.find(Format(L"magic",i))->second->setText(enemy_m->answers_m.magic_m[i]);
		objects.find(Format(L"special",i))->second->setText(enemy_m->answers_m.special_m[i]);
	}

	// ����ȓG�̎��J�b�g�C��������	
	if (id == 16 || id == 22 || id == 29) { cutIn_m->init(); }
	else{ cutIn_m->hide(); }


	if(id == 2 || id == 17 || id==18){
		enemy_m->messages_m.onPlayerWon_m.append(L"�N���b�N�Ŏ��ւ�����...");
	}
	else {
		enemy_m->messages_m.onPlayerWon_m.append(L"\n�N���b�N�Ŏ��ւ�����...");
	}
	
	SoundAsset(L"bettle_entry").setSpeed(0.5);
	SoundAsset(L"bettle_entry").play();
}
