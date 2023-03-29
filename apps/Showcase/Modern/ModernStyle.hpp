#pragma once

#include <QObject>
#include <QtQml>

class ModernStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int elevation READ elevation WRITE setElevation NOTIFY elevationChanged)

  public:
    explicit ModernStyle(QObject* parent = nullptr);

    static ModernStyle* qmlAttachedProperties(QObject* object);

    int elevation() const;
    void setElevation(int elevation);

  signals:
    void elevationChanged();

  private:
    int m_elevation;
};

QML_DECLARE_TYPEINFO(ModernStyle, QML_HAS_ATTACHED_PROPERTIES)
