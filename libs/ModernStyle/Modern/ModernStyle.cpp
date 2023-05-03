#include "ModernStyle.hpp"

static const ModernStyle::Theme s_globalTheme = ModernStyle::Light;
static const QRgb s_primaryColorDark = 0xFF5C5C5C;
static const QRgb s_primaryColorLight = 0xFF3B3B3B;
static const QRgb s_accentColorDark = 0xFFF49C1C;
static const QRgb s_accentColorLight = 0xFF5F83C1;
static const QRgb s_backgroundColorLight = 0xFFB2B2B2;
static const QRgb s_backgroundColorDark = 0xFF484848;

ModernStyle::ModernStyle(QObject* parent)
  : QObject(parent)
{
    // Init attached childrens
    updateAttachedChildrens();

    QQuickItem* attacheeItem = qobject_cast<QQuickItem*>(parent);
    if(attacheeItem)
    {
        connect(attacheeItem, &QQuickItem::childrenChanged, [=]() {
            updateAttachedChildrens();
            propagateProperties();
        });
    }
}

ModernStyle::~ModernStyle() {}

ModernStyle* ModernStyle::qmlAttachedProperties(QObject* object) { return new ModernStyle(object); }

ModernStyle::Theme ModernStyle::theme() const { return m_theme; }

void ModernStyle::setTheme(Theme theme)
{
    m_explicitTheme = true;
    if(theme == m_theme)
    {
        return;
    }
    m_theme = theme;
    propagateTheme();
    themeChange();
    if(!m_explicitPrimaryColor)
    {
        primaryColorChange();
    }
    if(!m_explicitAccentColor)
    {
        accentColorChange();
    }
}

void ModernStyle::inheritTheme(Theme theme)
{
    if(m_explicitTheme || m_theme == theme)
    {
        return;
    }
    m_theme = theme;
    propagateTheme();
    themeChange();
    if(!m_customPrimaryColor)
    {
        primaryColorChange();
    }
    if(!m_customAccentColor)
    {
        accentColorChange();
    }
}

void ModernStyle::propagateTheme()
{
    for(auto attachedChild : m_attachedChildrens)
    {
        attachedChild->inheritTheme(m_theme);
    }
}

void ModernStyle::resetTheme()
{
    if(!m_explicitTheme)
    {
        return;
    }
    m_explicitTheme = false;
    ModernStyle* modernStyleParent = attachedParent();
    inheritTheme(modernStyleParent ? modernStyleParent->theme() : s_globalTheme);
}

void ModernStyle::themeChange()
{
    emit themeChanged();
    emit backgroundColorChanged();
}

QColor ModernStyle::primaryColor() const
{
    if(m_customPrimaryColor)
    {
        return m_primaryColor;
    }
    return (m_theme == Dark) ? s_primaryColorDark : s_primaryColorLight;
}

void ModernStyle::setPrimaryColor(QColor primaryColor)
{
    m_explicitPrimaryColor = true;
    m_customAccentColor = true;
    if(m_primaryColor == primaryColor)
    {
        return;
    }
    m_primaryColor = primaryColor;
    propagatePrimaryColor();
    primaryColorChange();
}

void ModernStyle::inheritPrimaryColor(QColor primaryColor, bool custom)
{
    if(m_explicitPrimaryColor || m_primaryColor == primaryColor)
    {
        return;
    }
    m_customAccentColor = true;
    m_primaryColor = primaryColor;
    propagatePrimaryColor();
    primaryColorChange();
}

void ModernStyle::propagatePrimaryColor()
{
    for(auto attachedChild : m_attachedChildrens)
    {
        attachedChild->inheritPrimaryColor(m_primaryColor, m_customPrimaryColor);
    }
}

void ModernStyle::resetPrimaryColor()
{
    if(!m_explicitPrimaryColor)
    {
        return;
    }
    m_explicitPrimaryColor = false;
    m_customPrimaryColor = false;
    ModernStyle* modernStyleParent = attachedParent();
    if(modernStyleParent)
    {
        inheritPrimaryColor(modernStyleParent->primaryColor(), modernStyleParent->m_customPrimaryColor);
        return;
    }
    inheritPrimaryColor(primaryColor(), m_customPrimaryColor);
}

void ModernStyle::primaryColorChange()
{
    emit primaryColorChanged();
    emit buttonColorChanged();
    emit buttonDisabledColorChanged();
}

QColor ModernStyle::accentColor() const
{
    if(m_customAccentColor)
    {
        return m_accentColor;
    }
    return (m_theme == Dark) ? s_accentColorDark : s_accentColorLight;
}

void ModernStyle::setAccentColor(QColor accentColor)
{
    m_explicitAccentColor = true;
    m_customAccentColor = true;
    if(m_accentColor == accentColor)
    {
        return;
    }
    m_accentColor = accentColor;
    propagateAccentColor();
    accentColorChange();
}

void ModernStyle::inheritAccentColor(QColor accentColor, bool custom)
{
    if(m_explicitAccentColor || m_accentColor == accentColor)
    {
        return;
    }
    m_accentColor = accentColor;
    m_customAccentColor = custom;
    propagateAccentColor();
    accentColorChange();
}

void ModernStyle::propagateAccentColor()
{
    for(auto attachedChild : m_attachedChildrens)
    {
        attachedChild->inheritAccentColor(m_accentColor, m_customAccentColor);
    }
}

void ModernStyle::resetAccentColor()
{
    if(!m_explicitAccentColor)
    {
        return;
    }
    m_explicitAccentColor = false;
    m_customAccentColor = false;
    ModernStyle* modernStyleParent = attachedParent();
    if(modernStyleParent)
    {
        inheritPrimaryColor(modernStyleParent->accentColor(), modernStyleParent->m_customAccentColor);
        return;
    }
    inheritAccentColor(accentColor(), m_customAccentColor);
}

void ModernStyle::accentColorChange()
{
    emit accentColorChanged();
    emit hoveredButtonColorChanged();
}

bool ModernStyle::highlighted() const { return m_highlighted; }

void ModernStyle::setHighlighted(bool highlighted)
{
    m_explicitHighlighted = true;
    if(highlighted == m_highlighted)
    {
        return;
    }
    m_highlighted = highlighted;
    propagateHighlighted();
    highlightedChange();
}

void ModernStyle::inheritHighlighted(bool highlighted)
{
    if(m_explicitHighlighted || m_explicitHighlighted == highlighted)
    {
        return;
    }
    m_explicitHighlighted = highlighted;
    propagateHighlighted();
    highlightedChange();
}

void ModernStyle::propagateHighlighted()
{
    for(auto attachedChild : m_attachedChildrens)
    {
        attachedChild->inheritHighlighted(m_highlighted);
    }
}

void ModernStyle::resetHighlighted()
{
    if(!m_explicitHighlighted)
    {
        return;
    }
    m_explicitHighlighted = false;
    ModernStyle* modernStyleParent = attachedParent();
    inheritHighlighted(modernStyleParent ? modernStyleParent->highlighted() : false);
}

void ModernStyle::highlightedChange()
{
    emit highlightedChanged();
    emit buttonColorChanged();
}

QColor ModernStyle::backgroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? s_backgroundColorLight : s_backgroundColorDark);
}

QColor ModernStyle::buttonColor() const { return m_highlighted ? accentColor() : primaryColor(); }

QColor ModernStyle::buttonDisabledColor() const
{
    QColor normal = primaryColor();
    if(m_theme == Dark)
    {
        return normal.darker(200);
    }
    else
    {
        return normal.lighter(200);
    }
}

QColor ModernStyle::hoveredButtonColor() const
{
    QColor normal = buttonColor();
    if(m_theme == Dark)
    {
        return normal.lighter(150);
    }
    else
    {
        return normal.darker(150);
    }
}

void ModernStyle::updateAttachedChildrens()
{
    m_attachedChildrens.clear();
    auto childrens = findAttachedChildren(QObject::parent());
    for(auto child : childrens)
    {
        auto attachedPropertiesObject = qmlAttachedPropertiesObject<ModernStyle>(child);
        if(attachedPropertiesObject)
        {
            m_attachedChildrens += qobject_cast<ModernStyle*>(attachedPropertiesObject);
        }
    }
}

/**
 * There is 3 types of qml objects that can have the style attached property:
 * - classic visual element that inherit QQuickItem
 * - windows that inherit QQuickWindow
 * - popups that inherit QQuickPopup, but QQuickPopup is part of the private API so we can only use QObject
 * Then, when searching for attached children, if the children is a QQuickItem or a QQuickWindow,
 * the attached property will be created if needed, but if the children is a QObject, the attached property
 * will not be automatically  created in case the QObject is not a popup.
 */
QList<QObject*> ModernStyle::findAttachedChildren(QObject* parent)
{
    QList<QObject*> childrenObjects;

    // Parent is a QQuickItem
    QQuickItem* attacheeItem = qobject_cast<QQuickItem*>(parent);
    if(attacheeItem)
    {
        auto childItems = attacheeItem->childItems();
        // Add child Items
        std::transform(childItems.begin(), childItems.end(), std::back_inserter(childrenObjects), [](auto& item) {
            return qobject_cast<QObject*>(item);
        });

        // Add child windows and popups
        for(auto child : attacheeItem->children())
        {
            // If child is a QQuickWindow, add it to the list of childrens
            if(child->isWindowType())
            {
                childrenObjects.push_back(qobject_cast<QObject*>(child));
            }
            else
            {
                ModernStyle* modernStyleAttached =
                  static_cast<ModernStyle*>(qmlAttachedPropertiesObject<ModernStyle>(child, false));
                if(modernStyleAttached)
                {
                    childrenObjects.push_back(child);
                }
                else
                {
                    childrenObjects += findAttachedChildren(child);
                }
            }
        }
        return childrenObjects;
    }

    // Parent is a QQuickWindow
    QQuickWindow* attacheeWindow = qobject_cast<QQuickWindow*>(parent);
    if(attacheeWindow)
    {
        // Add child Items
        auto childItems = attacheeWindow->contentItem()->childItems();
        std::transform(childItems.begin(), childItems.end(), std::back_inserter(childrenObjects), [](auto& item) {
            return qobject_cast<QObject*>(item);
        });

        // Add child windows and popups
        for(auto child : attacheeWindow->children())
        {
            // If child is a QQuickWindow, add it to the list of childrens
            if(child->isWindowType())
            {
                childrenObjects.push_back(qobject_cast<QObject*>(child));
            }
            else
            {
                ModernStyle* modernStyleAttached =
                  static_cast<ModernStyle*>(qmlAttachedPropertiesObject<ModernStyle>(child, false));
                if(modernStyleAttached)
                {
                    childrenObjects.push_back(child);
                }
                else
                {
                    childrenObjects += findAttachedChildren(child);
                }
            }
        }
        return childrenObjects;
    }

    // Parent is a Popup
    auto popupChildrens = parent->children();
    for(auto child : popupChildrens)
    {
        // If the child is a QQuickItem, add it to the list of children objects
        QQuickItem* childItem = qobject_cast<QQuickItem*>(child);
        if(childItem)
        {
            childrenObjects.push_back(child);
            continue;
        }

        // If the child is a QQuickWindow, add it to the list of children objects
        if(child->isWindowType())
        {
            childrenObjects.push_back(child);
            continue;
        }

        // If the child is a QObject, it can be a QQuickPopup or something else,
        // so do not create the attached property but retrieve it if it already exist.
        // If it doesn't exist loop through the childrens of the QObject.
        ModernStyle* modernStyleAttached =
          static_cast<ModernStyle*>(qmlAttachedPropertiesObject<ModernStyle>(child, false));
        if(modernStyleAttached)
        {
            childrenObjects.push_back(child);
        }
        else
        {
            childrenObjects += findAttachedChildren(child);
        }
    }
    return childrenObjects;
}

ModernStyle* ModernStyle::attachedParent()
{
    QObject* parent = QObject::parent();
    QObject* grandParent = parent->parent();
    if(grandParent)
    {
        return static_cast<ModernStyle*>(qmlAttachedPropertiesObject<ModernStyle>(grandParent, false));
    }
    return nullptr;
}

void ModernStyle::propagateProperties() { propagateTheme(); }
