#pragma once

#include<Siv3D.hpp>
#include"../../Button/BasicButton.h"
#include"../../Drawable/Drawable.h"

namespace scene {
namespace title {

class Title;


class TitleButton : public BasicButton, public Drawable
{
protected:
    double const rectColorH_m;
    String const text_m;
    RoundRect const rect_m;
    std::shared_ptr<Title> const title_m;

    static String const FONT_NAME;
    static int const W;
    static int const H;
    static double const SCALE;
public:
    TitleButton(double colorH, String text, Point center, std::shared_ptr<Title> title);
    void draw()const;
    virtual ~TitleButton() = default;
};

class StartGame : public TitleButton
{
public:
    StartGame(std::shared_ptr<Title> title);
    void onClicked()override;
};

class GoToRule : public TitleButton
{
public:
    GoToRule(std::shared_ptr<Title> title);
    void onClicked()override;
};

class DefeatedEnemies : public TitleButton
{
public:
    DefeatedEnemies(std::shared_ptr<Title> title);
    void onClicked()override;
};

class QuitGame : public TitleButton
{
public:
    QuitGame(std::shared_ptr<Title> title);
    void onClicked()override;
};

}
}
