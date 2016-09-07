#include "MyDrawableList.h"



MyDrawableList::~MyDrawableList()
{
}

void MyDrawableList::add(std::shared_ptr<Drawable> drawable, int layer)
{
	m_drawables.insert(std::make_pair(layer, drawable));
}

void MyDrawableList::drawAll() const
{
	std::for_each(m_drawables.begin(), m_drawables.end(), [](auto p) {
		if (p.second->isVisible()) {
			p.second->draw();
		}
	});
}


void MyDrawableList::drawLayer(int layer) const
{
	auto itr = m_drawables.find(layer);
	if (itr->second->isVisible()) {
		itr->second->draw();
	}
}
