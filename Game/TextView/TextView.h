#pragma once

#include <Siv3D.hpp>
#include "../Drawable/Drawable.h"

class TextView
	:public Drawable
{
public:
	/// <summary>
	/// １文字づつ表示される文字列
	/// </summary>
	/// <param name='text'> 表示する文字列 </param>
	/// <param name='pos'> 表示領域の左上の座標 </param>
	/// <param name='width'> 表示領域の幅 </param>
	/// <param name='lines'> 最大行数 </param>
	/// <param name='font'> フォント </param>
	/// <param name='Interval'> 文字を追加する間隔 </param>
	TextView(const String& text, const Point& pos, const int width, const int lines, const Font& font, int IntervalIncrease=3,Color color = Palette::White);

	~TextView();

	/// <summary>
	/// 更新する
	/// </summar>
	void update();

	/// <summary>
	/// 描画する
	/// </summary>
	void draw()const;

	/// <summary>
	/// テキストを変更する
	/// </summary>
	/// <param name='text'> 新しい表示する文字列 </param> 
	void setNewText(const String& text);

	/// <summary>
	/// テキストが全て表示されているか
	/// </summary>
	/// <returns>  </returns>
	bool isPlotAll()const;

	/// <summary>
	/// 全てのテキストが表示された状態にする
	/// </summary>
	void setPlotAll();

	/// <summary>
	/// 文字が追加される間隔を変える
	/// </summary>
	/// <param name='interval'>追加する間隔</param>
	void setIntervalIncrease(int interval);

	/// <summary>
	/// デバッグ文や描画領域を表示する
	/// </summary>
	void debugDraw()const;

private:
	//１文字を追加
	void addCharacter();
	int getStrRigthPos();
private:
	String str_m;					//表示する文字列
	Font font_m;					//フォント
	Point pos_m;					//描画位置(左上)
	int PositionToBreak_m;			//このX座標を越えると自動改行する
	unsigned lines_m;				//現在の行数
	unsigned maxLines_m;			//最大行数
	unsigned count_m;				//現在の表示文字数
	bool isAutomaticLineBreak;		//自動改行するか
	unsigned IntervalIncrease_m;	//文字を増やす間隔(フレーム)
	Color color_m;					//文字色
};
