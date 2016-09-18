#include "RegisterAsset.h"



RegisterAsset::RegisterAsset()
{
	TextureAsset::Register(L"title_graphicM", L"/1200");
	TextureAsset::Register(L"title_logo2M", L"/1201");
	TextureAsset::Register(L"start_buttonM", L"/1202");
	TextureAsset::Register(L"RuleButtonM", L"/1203");
	TextureAsset::Register(L"EnemiesButtonM", L"/1204");
	TextureAsset::Register(L"CreditButtonM", L"/1205");
	TextureAsset::Register(L"QuitButtonM", L"/1206");
	TextureAsset::Register(L"StartButtonL", L"/1207");
	TextureAsset::Register(L"back_button_resize", L"/1208");
	TextureAsset::Register(L"Rule", L"/1209");
	TextureAsset::Register(L"right_button_resize", L"/1210");
	TextureAsset::Register(L"left_button_resize", L"/1211");
	TextureAsset::Register(L"title_button_resize", L"/1212");

	TextureAsset::Register(L"title_button", L"/1300");
	TextureAsset::Register(L"left_button", L"/1301");
	TextureAsset::Register(L"right_button", L"/1302");
	TextureAsset::Register(L"firstEnemiesBackGround", L"/1303");
	TextureAsset::Register(L"secondEnemiesBackGround", L"/1303");
	TextureAsset::Register(L"enemies_logo", L"/1304");
	SoundAsset::Register(L"enemies_bgm", L"/1310");
	SoundAsset::Register(L"enemies_decide", L"/1311");
	SoundAsset::Register(L"enemies_move", L"/1312");
	SoundAsset::Register(L"enemies_return", L"/1313");

	FontAsset::Register(L"BattleSceneFont", 20);
	TextureAsset::Register(L"mesWindow", L"/1501");
	TextureAsset::Register(L"miniMesWindow", L"/1502");
	TextureAsset::Register(L"battleButton", L"/1500");
	TextureAsset::Register(L"CutInEffect", L"/1503");
	for (int i = 1; i <= 5; i++) { TextureAsset::Register(Format(L"battleBack", i), Format(L"/", (1510 + i))); }
	//SoundAsset::Register(L"battle_bgm", L"/1520");
	SoundAsset::Register(L"battle_corect", L"/1521");
	SoundAsset::Register(L"battle_incorect", L"/1522");	
	SoundAsset::Register(L"bettle_GameOver", L"/1523");
	SoundAsset::Register(L"bettle_entry", L"/1524");
	for (int i = 0; i < 4; i++) { SoundAsset::Register(Format(L"battle_bgm",i),Format(L"/",(1525 + i))); }

	TextureAsset::Register(L"Enemy1", L"/1601");
	TextureAsset::Register(L"Enemy2", L"/1602");
	TextureAsset::Register(L"Enemy3", L"/1603");
	TextureAsset::Register(L"Enemy4", L"/1604");
	TextureAsset::Register(L"Enemy5", L"/1605");
	TextureAsset::Register(L"Enemy6", L"/1606");
	TextureAsset::Register(L"Enemy7", L"/1607");
	TextureAsset::Register(L"Enemy8", L"/1608");
	TextureAsset::Register(L"Enemy9", L"/1609");
	TextureAsset::Register(L"Enemy10", L"/1610");
	TextureAsset::Register(L"Enemy11", L"/1611");
	TextureAsset::Register(L"Enemy12", L"/1612");
	TextureAsset::Register(L"Enemy13", L"/1613");
	TextureAsset::Register(L"Enemy14", L"/1614");
	TextureAsset::Register(L"Enemy15", L"/1615");
	TextureAsset::Register(L"Enemy16", L"/1616");
	TextureAsset::Register(L"Enemy17", L"/1617");
	TextureAsset::Register(L"Enemy18", L"/1618");
	TextureAsset::Register(L"Enemy19", L"/1619");
	TextureAsset::Register(L"Enemy20", L"/1620");
	TextureAsset::Register(L"Enemy21", L"/1621");
	TextureAsset::Register(L"Enemy22", L"/1622");
	TextureAsset::Register(L"Enemy23", L"/1623");
	TextureAsset::Register(L"Enemy24", L"/1624");
	TextureAsset::Register(L"Enemy25", L"/1625");
	TextureAsset::Register(L"Enemy26", L"/1626");
	TextureAsset::Register(L"Enemy27", L"/1627");
	TextureAsset::Register(L"Enemy28", L"/1628");
	TextureAsset::Register(L"Enemy29", L"/1629");
	TextureAsset::Register(L"Enemy30", L"/1630");

	TextureAsset::Register(L"ShadowEnemy1", L"/1701");
	TextureAsset::Register(L"ShadowEnemy2", L"/1702");
	TextureAsset::Register(L"ShadowEnemy3", L"/1703");
	TextureAsset::Register(L"ShadowEnemy4", L"/1704");
	TextureAsset::Register(L"ShadowEnemy5", L"/1705");
	TextureAsset::Register(L"ShadowEnemy6", L"/1706");
	TextureAsset::Register(L"ShadowEnemy7", L"/1707");
	TextureAsset::Register(L"ShadowEnemy8", L"/1708");
	TextureAsset::Register(L"ShadowEnemy9", L"/1709");
	TextureAsset::Register(L"ShadowEnemy10", L"/1710");
	TextureAsset::Register(L"ShadowEnemy11", L"/1711");
	TextureAsset::Register(L"ShadowEnemy12", L"/1712");
	TextureAsset::Register(L"ShadowEnemy13", L"/1713");
	TextureAsset::Register(L"ShadowEnemy14", L"/1714");
	TextureAsset::Register(L"ShadowEnemy15", L"/1715");
	TextureAsset::Register(L"ShadowEnemy16", L"/1716");
	TextureAsset::Register(L"ShadowEnemy17", L"/1717");
	TextureAsset::Register(L"ShadowEnemy18", L"/1718");
	TextureAsset::Register(L"ShadowEnemy19", L"/1719");
	TextureAsset::Register(L"ShadowEnemy20", L"/1720");
	TextureAsset::Register(L"ShadowEnemy21", L"/1721");
	TextureAsset::Register(L"ShadowEnemy22", L"/1722");
	TextureAsset::Register(L"ShadowEnemy23", L"/1723");
	TextureAsset::Register(L"ShadowEnemy24", L"/1724");
	TextureAsset::Register(L"ShadowEnemy25", L"/1725");
	TextureAsset::Register(L"ShadowEnemy26", L"/1726");
	TextureAsset::Register(L"ShadowEnemy27", L"/1727");
	TextureAsset::Register(L"ShadowEnemy28", L"/1728");
	TextureAsset::Register(L"ShadowEnemy29", L"/1729");
    TextureAsset::Register(L"ShadowEnemy30", L"/1730");

    TextureAsset::Register(L"Result_Background", L"/1801");
    TextureAsset::Register(L"Result_Logo", L"/1802");
    TextureAsset::Register(L"Result_RetryButton", L"/1803");
    TextureAsset::Register(L"Result_TitleButton", L"/1804");
	SoundAsset::Register(L"Result_BGM", L"/1811");
	SoundAsset::Register(L"Result_ButtonSE", L"/1812");
	FontAsset::Register(L"Result_Font", FontAssetData(30, Typeface::Heavy, FontStyle::Outline));
    FontAsset(L"Result_Font").changeOutlineStyle(TextOutlineStyle(Palette::Black, Palette::White, 2.0));

	//全てプリロード
	TextureAsset::PreloadAll();
	SoundAsset::PreloadAll();
    FontAsset::PreloadAll();

}

RegisterAsset::~RegisterAsset()
{
    TextureAsset::ReleaseAll();
    SoundAsset::ReleaseAll();
    FontAsset::ReleaseAll();
}
