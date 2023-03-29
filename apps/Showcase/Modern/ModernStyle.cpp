#include "ModernStyle.hpp"

ModernStyle::ModernStyle(QObject* parent)
  : QObject(parent)
  , m_elevation(0)
{}

ModernStyle* ModernStyle::qmlAttachedProperties(QObject* object) { return new ModernStyle(object); }

int ModernStyle::elevation() const { return m_elevation; }

void ModernStyle::setElevation(int elevation)
{
    if(elevation == m_elevation)
    {
        return;
    }
    m_elevation = elevation;
    emit elevationChanged();
}
