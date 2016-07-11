#pragma once

#include <map>
#include <memory>
#include <algorithm>
#include "Drawable.h"

class DrawableList
{
private:
    std::multimap<int, std::shared_ptr<Drawable>> m_drawables;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DrawableList() = default;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DrawableList();

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
};

