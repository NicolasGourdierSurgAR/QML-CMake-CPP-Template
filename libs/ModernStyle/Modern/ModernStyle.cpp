#include "ModernStyle.hpp"

static const ModernStyle::Theme s_globalTheme = ModernStyle::Light;
static const QRgb s_backgroundColorLight = 0xFFFAFAFA;
static const QRgb s_backgroundColorDark = 0xFF303030;

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
    ModernStyle* modernStyleParent = attachedParent();
    inheritTheme(modernStyleParent ? modernStyleParent->theme() : s_globalTheme);
}

void ModernStyle::themeChange()
{
    emit themeChanged();
    emit backgroundColorChanged();
}

QColor ModernStyle::backgroundColor() const
{
    return QColor::fromRgba(m_theme == Light ? s_backgroundColorLight : s_backgroundColorDark);
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
