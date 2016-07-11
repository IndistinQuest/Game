#pragma once
#include "ButtonInterface.h"
#include<Siv3D.hpp>

class BasicButton :
    public ButtonInterface
{
private:
    State state_m = State::LEFT;
    bool isEnabled_m = true;
    Shape const shape_m;
public:
    explicit BasicButton(Shape shape);
    virtual void onClicked() = 0;
    virtual void transition()override;
    State getState()const override;
    bool isEnabled()const;
    void enable();
    void disable();
    virtual ~BasicButton() = default;
protected:
    void setState(State state);
};

