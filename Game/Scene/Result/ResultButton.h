#pragma once

#include <Siv3D.hpp>
#include "Result.h"
#include "../../Button/BasicButton.h"
#include "../../Drawable/Drawable.h"

namespace scene
{
namespace result
{

class ResultButton : public BasicButton, public Drawable
{
protected:
    static const int WIDTH;
    static const int HEIGHT;
    static const String FONT_NAME;
protected:
    const String text_m;
    const RoundRect rect_m;
    const std::shared_ptr<Result> result_m;
public:
    ResultButton(const String text, const Point position, std::shared_ptr<Result> result);
    ~ResultButton() = default;
public:
    void draw() const override;
};


class OneMoreGame : public ResultButton
{
public:
    OneMoreGame(const std::shared_ptr<Result> result);
public:
    void onClicked() override;
};


class GoToTitle : public ResultButton
{
public:
    GoToTitle(const std::shared_ptr<Result> result);
public:
    void onClicked() override;
};

}
}
