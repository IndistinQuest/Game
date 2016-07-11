#include "DrawableList.h"



DrawableList::~DrawableList()
{
}

void DrawableList::add(std::shared_ptr<Drawable> drawable, int layer)
{
    m_drawables.insert(std::make_pair(layer, drawable));
}

void DrawableList::drawAll() const
{
    std::for_each(m_drawables.begin(), m_drawables.end(), [](auto p) {
        if(p.second->isVisible()) {
            p.second->draw();
        }
    });
}
