#pragma once

#include <QObject>
#include <QQuickItem>
#include <QQuickWindow>
#include <QtQml>

class ModernStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged)
    Q_PROPERTY(int elevation READ elevation WRITE setElevation NOTIFY elevationChanged)

  public:
    enum Theme
    {
        Light,
        Dark
    };

    // Q_ENUM(Theme)

    explicit ModernStyle(QObject* parent = nullptr);
    ~ModernStyle();

    static ModernStyle* qmlAttachedProperties(QObject* object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();
    void themeChange();

    int elevation() const;
    void setElevation(int elevation);
    void propagateElevation();
    void inheritPrimary(int elevation);

  signals:
    void themeChanged();
    void elevationChanged();

  private:
    QList<QObject*> findAttachedChildren(QObject* parent);
    ModernStyle* attachedParent();
    void updateAttachedChildrens();
    void propagateProperties();

  private:
    Theme m_theme{Light};
    bool m_explicitTheme{false};

    int m_elevation;
    bool m_explicitElevation{false};
    QList<ModernStyle*> m_attachedChildrens;
};

QML_DECLARE_TYPEINFO(ModernStyle, QML_HAS_ATTACHED_PROPERTIES)
