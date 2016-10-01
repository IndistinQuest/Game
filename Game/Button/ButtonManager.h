#pragma once

#include<memory>
#include<list>

class ButtonInterface;

class ButtonManager
{
private:
    static std::list<std::shared_ptr<ButtonInterface>> buttons_m;
    static bool isClearing_m;
public:
    ButtonManager() = default;
    ~ButtonManager() = default;
    static void add(std::shared_ptr<ButtonInterface> const &button);
    static void update();
    static void clearAll();
};

