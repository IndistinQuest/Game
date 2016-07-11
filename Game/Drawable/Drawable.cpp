#include "Drawable.h"


Drawable::Drawable()
    : m_isVisible(true)
{
}

void Drawable::show()
{
    m_isVisible = true;
}

void Drawable::hide()
{
    m_isVisible = false;
}

bool Drawable::isVisible() const
{
    return m_isVisible;
}
