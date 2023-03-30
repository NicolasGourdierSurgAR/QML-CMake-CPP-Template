#pragma once

#include "FileWatcher.hpp"

#include <QQmlApplicationEngine>

/*
 * Based on Marko Stanojevic work
 */

class LiveReloadEngine : public QQmlApplicationEngine
{
    Q_OBJECT
  public:
    LiveReloadEngine(QObject* parent = nullptr);

    Q_INVOKABLE void clearCache();

  private:
    FileWatcher* m_fileWatcher;

  signals:
    void reloadUI();
};
