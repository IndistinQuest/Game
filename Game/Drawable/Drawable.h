#pragma once

#include <Siv3D.hpp>

/// <summary>
/// 描画するオブジェクトのインターフェース
/// </summary>
class Drawable
{
private:
    bool m_isVisible;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Drawable();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Drawable() = default;
public:
    /// <summary>
    /// 描画する
    /// </summary>
    virtual void draw() const = 0;
    
    /// <summary>
    /// オブジェクトを表示する
    /// </summary>
    void show();

    /// <summary>
    /// オブジェクトを非表示にする
    /// </summary>
    void hide();

    /// <summary>
    /// オブジェクトの表示状態を取得する
    /// </summary>
    /// <returns> 表示状態 </returns>
    bool isVisible() const;
};

