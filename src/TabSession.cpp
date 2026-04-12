#include "TabSession.h"
#include "TabView.h"

TabSession::TabSession(const QString& title, QObject* parent)
    : QObject(parent), m_title(title) {
    m_icon = QIcon(":/src/icons/tab.svg");
}

void TabSession::setTitle(const QString& title) {
    if (m_title != title) {
        m_title = title;
        emit titleChanged(m_title);
    }
}

void TabSession::setIcon(const QIcon& icon) {
    m_icon = icon;
    emit iconChanged(m_icon);
}

void TabSession::setView(TabView* view) {
    m_view = view;
}

void TabSession::setModuleType(ModuleType type) {
    if (m_moduleType != type) {
        m_moduleType = type;
        emit moduleTypeChanged(type);
    }
}

void TabSession::setDirty(bool dirty) {
    if (m_isDirty != dirty) {
        m_isDirty = dirty;
        emit dirtyChanged(m_isDirty);
    }
}
