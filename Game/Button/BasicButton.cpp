#include "BasicButton.h"



BasicButton::BasicButton(Shape shape)
    :shape_m(shape)
{}

void BasicButton::transition()
{
    switch (state_m) {
    case State::LEFT:
        if (shape_m.mouseOver && !shape_m.leftPressed) {
            state_m = State::MOUSE_OVER;
        }
        else {
        }
        break;
    case State::MOUSE_OVER:
        if (shape_m.leftPressed) {
            state_m = State::PRESSED;
        }
        else if (!shape_m.mouseOver) {
            state_m = State::LEFT;
        }
        else {
        }
        break;
    case State::PRESSED:
        if (!shape_m.mouseOver) {
            state_m = State::LEFT;
        }
        else if (shape_m.leftReleased) {
            state_m = State::RELEASED;
        }
        break;
    case State::RELEASED:
        state_m = State::LEFT;
        break;
    case State::REMOVED:
        break;
    default:
        break;
    }
}
BasicButton::State BasicButton::getState()const
{
    return state_m;
}

void BasicButton::setState(State state)
{
    state_m = state;
}

bool BasicButton::isEnabled()const
{
    return isEnabled_m;
}

void BasicButton::enable()
{
    isEnabled_m = true;
}

void BasicButton::disable()
{
    isEnabled_m = false;
}


