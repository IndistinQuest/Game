#pragma once

#include<Siv3D.hpp>
#include<functional>
#include"BasicButton.h"

class LambdaButton : public BasicButton
{
private:
    std::function<void(void)> handler_m;
public:
    void onClicked()override;
    LambdaButton(Shape shape, std::function<void(void)> handler);
    virtual ~LambdaButton() = default;
};

