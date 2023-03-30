#include "LiveReloadEngine.hpp"

LiveReloadEngine::LiveReloadEngine(QObject* parent)
  : QQmlApplicationEngine(parent)
{
#ifdef QT_DEBUG
    m_fileWatcher = new FileWatcher(this);

    QObject::connect(m_fileWatcher, &FileWatcher::reloadUI, this, &LiveReloadEngine::reloadUI);
#endif
}

void LiveReloadEngine::clearCache() { this->clearComponentCache(); }
