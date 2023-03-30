#pragma once

/*
 * Based on Marko Stanojevic work
 */

#include <QDir>
#include <QFileSystemWatcher>
#include <QObject>
#include <QTimer>

#include <functional>

class FileWatcher : public QObject
{
    Q_OBJECT
  public:
    FileWatcher(QObject* parent = nullptr);
    void setDirectory(const QString& path);

  private:
    void addPaths(QDir& directory);

  public slots:
    void onDirectoryChanged(const QString& path);
    void onFileChanged(const QString& path);

  signals:
    void reloadUI();

  private:
    QFileSystemWatcher m_watcher;
    QDir m_dir;
    QTimer m_timer;
};
