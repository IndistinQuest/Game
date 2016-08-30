#pragma once

#include <map>
#include <memory>
#include <algorithm>
#include "../../Drawable/Drawable.h"
#include "../../Drawable/DrawableList.h"

class MyDrawableList : public DrawableList
{
private:
	std::multimap<int, std::shared_ptr<Drawable>> m_drawables;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MyDrawableList() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MyDrawableList();

public:
	/// <summary>
	/// 描画リストに追加する
	/// </summary>
	/// <param name="drawable"> 描画するオブジェクト </param>
	/// <param name="layer"> レイヤー番号 </param>
	void add(std::shared_ptr<Drawable> drawable, int layer);

	/// <summary>
	/// 全てのオブジェクトを描画する
	/// </summary>
	void drawAll() const;
	/// <summary>
	/// 指定のレイヤのみを描画する
	/// <param namme="layer"> 描画するレイヤー番号 </param>
	/// </summary>
	void drawLayer(int layer) const;
};

