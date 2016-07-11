#pragma once

#include<memory>
#include<list>

class ButtonInterface;

class ButtonManager
{
private:
    static std::list<std::shared_ptr<ButtonInterface>> buttons_m;
public:
    ButtonManager();
    ~ButtonManager();
    static void add(std::shared_ptr<ButtonInterface> const &button);
    static void update();
};

