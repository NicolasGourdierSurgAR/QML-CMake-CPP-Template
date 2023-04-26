#pragma once

#include <QColor>
#include <QObject>
#include <QQuickItem>
#include <QQuickWindow>
#include <QtQml>

class ModernStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY backgroundColorChanged)

  public:
    enum Theme
    {
        Light,
        Dark
    };

    Q_ENUM(Theme)

    explicit ModernStyle(QObject* parent = nullptr);
    ~ModernStyle();

    static ModernStyle* qmlAttachedProperties(QObject* object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();
    void themeChange();

    QColor backgroundColor() const;

  signals:
    void themeChanged();
    void backgroundColorChanged();

  private:
    QList<QObject*> findAttachedChildren(QObject* parent);
    ModernStyle* attachedParent();
    void updateAttachedChildrens();
    void propagateProperties();

  private:
    Theme m_theme{Light};
    bool m_explicitTheme{false};

    QColor m_backgroundColor{};
    bool m_explicitBackgroundColor{false};

    QList<ModernStyle*> m_attachedChildrens;
};

QML_DECLARE_TYPEINFO(ModernStyle, QML_HAS_ATTACHED_PROPERTIES)
