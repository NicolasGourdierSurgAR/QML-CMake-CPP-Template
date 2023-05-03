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
    Q_PROPERTY(
      QColor primaryColor READ primaryColor WRITE setPrimaryColor RESET resetPrimaryColor NOTIFY primaryColorChanged)
    Q_PROPERTY(
      QColor accentColor READ accentColor WRITE setAccentColor RESET resetAccentColor NOTIFY accentColorChanged)

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

    QColor primaryColor() const;
    void setPrimaryColor(QColor primarycolor);
    void inheritPrimaryColor(QColor primarycolor, bool custom);
    void propagatePrimaryColor();
    void resetPrimaryColor();
    void primaryColorChange();

    QColor accentColor() const;
    void setAccentColor(QColor accentcolor);
    void inheritAccentColor(QColor accentcolor, bool custom);
    void propagateAccentColor();
    void resetAccentColor();
    void accentColorChange();

    QColor backgroundColor() const;

  signals:
    void themeChanged();
    void primaryColorChanged();
    void accentColorChanged();
    void backgroundColorChanged();

  private:
    QList<QObject*> findAttachedChildren(QObject* parent);
    ModernStyle* attachedParent();
    void updateAttachedChildrens();
    void propagateProperties();

  private:
    Theme m_theme{Light};
    bool m_explicitTheme{false};

    QColor m_primaryColor{};
    bool m_explicitPrimaryColor{false};
    bool m_customPrimaryColor{false};

    QColor m_accentColor{};
    bool m_explicitAccentColor{false};
    bool m_customAccentColor{false};

    QColor m_backgroundColor{};

    QList<ModernStyle*> m_attachedChildrens;
};

QML_DECLARE_TYPEINFO(ModernStyle, QML_HAS_ATTACHED_PROPERTIES)
