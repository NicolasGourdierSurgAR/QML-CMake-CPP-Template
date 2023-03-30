#include "FileWatcher.hpp"

#include <QDebug>

#include <thread>

FileWatcher::FileWatcher(QObject* parent)
  : QObject(parent)
{
    QObject::connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::onDirectoryChanged);
    QObject::connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::onFileChanged);

    // Configure the timer to signal the changes to the callback
    m_timer.setInterval(150);
    m_timer.setSingleShot(true);

    // Connect the timer to the callback function
    QObject::connect(&m_timer, &QTimer::timeout, this, &FileWatcher::reloadUI);

    setDirectory(SOURCES_DIRECTORY);
}

void FileWatcher::setDirectory(const QString& path)
{
    QDir projectDir = QDir(path);

    if(!projectDir.exists())
    {
        qWarning() << "Directory " << path << " doesn't exist.";
        return;
    }
    qInfo() << "Directory for file watcher set to: " << path;

    m_dir = projectDir;
    addPaths(m_dir);
    qInfo() << "Finished: Number of qml files watched by the file watcher: " << m_watcher.files().count();
}

void FileWatcher::addPaths(QDir& directory)
{
    // Add qml files from the current directory
    QStringList qmlFiles = directory.entryList(QStringList() << "*.qml");
    for(int i = 0; i < qmlFiles.count(); ++i)
    {
        qmlFiles[i].prepend(directory.absolutePath() + "/");
    }

    if(qmlFiles.count() > 0)
    {
        m_watcher.addPaths(qmlFiles);
    }

    QStringList directories =
      directory.entryList(QStringList() << "*", QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    for(int i = 0; i < directories.count(); ++i)
    {
        directories[i].prepend(directory.absolutePath() + "/");
        QDir directory(directories[i]);
        addPaths(directory);
    }
}

void FileWatcher::onDirectoryChanged(const QString& path)
{
    Q_UNUSED(path);
    qInfo() << "Directory changed";
    m_watcher.removePaths(m_watcher.files());
    addPaths(m_dir);
}

void FileWatcher::onFileChanged(const QString& path)
{
    QFileInfo checkFile(path);
    while(!checkFile.exists())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    m_watcher.addPath(path);
    m_timer.start();
}
