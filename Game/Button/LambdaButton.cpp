#include "LambdaButton.h"

LambdaButton::LambdaButton(Shape shape, std::function<void(void)> handler)
    :BasicButton(shape), handler_m(handler){}

void LambdaButton::onClicked()
{
    handler_m();
}