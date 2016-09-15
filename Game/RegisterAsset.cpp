#include "RegisterAsset.h"



RegisterAsset::RegisterAsset()
{
	TextureAsset::Register(L"title_graphicM", L"/200");
	TextureAsset::Register(L"title_logo2M", L"/201");
	TextureAsset::Register(L"start_buttonM", L"/202");
	TextureAsset::Register(L"RuleButtonM", L"/203");
	TextureAsset::Register(L"EnemiesButtonM", L"/204");
	TextureAsset::Register(L"CreditButtonM", L"/205");
	TextureAsset::Register(L"QuitButtonM", L"/206");
	TextureAsset::Register(L"StartButtonL", L"/207");
	TextureAsset::Register(L"back_button_resize", L"/208");

	TextureAsset::Register(L"title_button", L"/300");
	TextureAsset::Register(L"left_button", L"/301");
	TextureAsset::Register(L"right_button", L"/302");
	TextureAsset::Register(L"firstEnemiesBackGround", L"/303");
	TextureAsset::Register(L"secondEnemiesBackGround", L"/303");
	TextureAsset::Register(L"enemies_logo", L"/304");
	SoundAsset::Register(L"enemies_bgm", L"/310");
	SoundAsset::Register(L"enemies_decide", L"/311");
	SoundAsset::Register(L"enemies_move", L"/312");
	SoundAsset::Register(L"enemies_return", L"/313");

	FontAsset::Register(L"BattleSceneFont", 20);
	TextureAsset::Register(L"mesWindow", L"/501");
	TextureAsset::Register(L"miniMesWindow", L"/502");
	TextureAsset::Register(L"battleButton", L"/500");
	TextureAsset::Register(L"CutInEffect", L"/503");
	for (int i = 1; i <= 5; i++) { TextureAsset::Register(Format(L"battleBack", i), Format(L"/", (510 + i))); }
	SoundAsset::Register(L"battle_bgm", L"/520");
	SoundAsset::Register(L"battle_corect", L"/521");
	SoundAsset::Register(L"battle_incorect", L"/522");	
	SoundAsset::Register(L"bettle_GameOver", L"/523");
	SoundAsset::Register(L"bettle_entry", L"/524");

	TextureAsset::Register(L"Enemy1", L"/601");
	TextureAsset::Register(L"Enemy2", L"/602");
	TextureAsset::Register(L"Enemy3", L"/603");
	TextureAsset::Register(L"Enemy4", L"/604");
	TextureAsset::Register(L"Enemy5", L"/605");
	TextureAsset::Register(L"Enemy6", L"/606");
	TextureAsset::Register(L"Enemy7", L"/607");
	TextureAsset::Register(L"Enemy8", L"/608");
	TextureAsset::Register(L"Enemy9", L"/609");
	TextureAsset::Register(L"Enemy10", L"/610");
	TextureAsset::Register(L"Enemy11", L"/611");
	TextureAsset::Register(L"Enemy12", L"/612");
	TextureAsset::Register(L"Enemy13", L"/613");
	TextureAsset::Register(L"Enemy14", L"/614");
	TextureAsset::Register(L"Enemy15", L"/615");
	TextureAsset::Register(L"Enemy16", L"/616");
	TextureAsset::Register(L"Enemy17", L"/617");
	TextureAsset::Register(L"Enemy18", L"/618");
	TextureAsset::Register(L"Enemy19", L"/619");
	TextureAsset::Register(L"Enemy20", L"/620");
	TextureAsset::Register(L"Enemy21", L"/621");
	TextureAsset::Register(L"Enemy22", L"/622");
	TextureAsset::Register(L"Enemy23", L"/623");
	TextureAsset::Register(L"Enemy24", L"/624");
	TextureAsset::Register(L"Enemy25", L"/625");
	TextureAsset::Register(L"Enemy26", L"/626");
	TextureAsset::Register(L"Enemy27", L"/627");
	TextureAsset::Register(L"Enemy28", L"/628");
	TextureAsset::Register(L"Enemy29", L"/629");
	TextureAsset::Register(L"Enemy30", L"/630");

	TextureAsset::Register(L"ShadowEnemy1", L"/701");
	TextureAsset::Register(L"ShadowEnemy2", L"/702");
	TextureAsset::Register(L"ShadowEnemy3", L"/703");
	TextureAsset::Register(L"ShadowEnemy4", L"/704");
	TextureAsset::Register(L"ShadowEnemy5", L"/705");
	TextureAsset::Register(L"ShadowEnemy6", L"/706");
	TextureAsset::Register(L"ShadowEnemy7", L"/707");
	TextureAsset::Register(L"ShadowEnemy8", L"/708");
	TextureAsset::Register(L"ShadowEnemy9", L"/709");
	TextureAsset::Register(L"ShadowEnemy10", L"/710");
	TextureAsset::Register(L"ShadowEnemy11", L"/711");
	TextureAsset::Register(L"ShadowEnemy12", L"/712");
	TextureAsset::Register(L"ShadowEnemy13", L"/713");
	TextureAsset::Register(L"ShadowEnemy14", L"/714");
	TextureAsset::Register(L"ShadowEnemy15", L"/715");
	TextureAsset::Register(L"ShadowEnemy16", L"/716");
	TextureAsset::Register(L"ShadowEnemy17", L"/717");
	TextureAsset::Register(L"ShadowEnemy18", L"/718");
	TextureAsset::Register(L"ShadowEnemy19", L"/719");
	TextureAsset::Register(L"ShadowEnemy20", L"/720");
	TextureAsset::Register(L"ShadowEnemy21", L"/721");
	TextureAsset::Register(L"ShadowEnemy22", L"/722");
	TextureAsset::Register(L"ShadowEnemy23", L"/723");
	TextureAsset::Register(L"ShadowEnemy24", L"/724");
	TextureAsset::Register(L"ShadowEnemy25", L"/725");
	TextureAsset::Register(L"ShadowEnemy26", L"/726");
	TextureAsset::Register(L"ShadowEnemy27", L"/727");
	TextureAsset::Register(L"ShadowEnemy28", L"/728");
	TextureAsset::Register(L"ShadowEnemy29", L"/729");
	TextureAsset::Register(L"ShadowEnemy30", L"/730");

	//全てプリロード
	//TextureAsset::PreloadAll();
	//SoundAsset::PreloadAll();
}

RegisterAsset::~RegisterAsset()
{
}
