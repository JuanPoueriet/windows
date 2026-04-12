#include "TabHost.h"
#include "DetachableTabBar.h"
#include "TabSession.h"
#include "TabView.h"
#include "WindowManager.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

TabHost::TabHost(QWidget* parent) : QWidget(parent) {
    setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_tabBar = new DetachableTabBar(this);
    m_tabBar->setTabsClosable(true);
    m_tabBar->setMovable(true);

    m_stackedWidget = new QStackedWidget(this);

    layout->addWidget(m_tabBar);
    layout->addWidget(m_stackedWidget);

    connect(m_tabBar, &QTabBar::currentChanged, this, &TabHost::onCurrentChanged);
    connect(m_tabBar, &QTabBar::tabCloseRequested, this, &TabHost::onTabCloseRequested);
}

TabHost::~TabHost() {
}

void TabHost::addTab(TabSession* session) {
    insertTab(m_sessions.size(), session);
}

void TabHost::insertTab(int index, TabSession* session) {
    if (index < 0 || index > static_cast<int>(m_sessions.size())) index = m_sessions.size();

    m_sessions.insert(m_sessions.begin() + index, session);
    int realIndex = m_tabBar->insertTab(index, session->icon(), session->title());
    m_stackedWidget->insertWidget(realIndex, session->view());

    session->view()->setParent(m_stackedWidget);
    m_tabBar->setCurrentIndex(realIndex);
}

void TabHost::removeTab(int index, bool deleteSession) {
    if (index < 0 || index >= static_cast<int>(m_sessions.size())) return;

    TabSession* session = m_sessions[index];
    m_tabBar->removeTab(index);
    m_stackedWidget->removeWidget(session->view());
    m_sessions.erase(m_sessions.begin() + index);

    if (deleteSession) {
        delete session->view();
        delete session;
    }

    if (m_sessions.empty()) {
        WindowManager::instance().notifyTabHostEmpty(this);
    }
}

TabSession* TabHost::getTab(int index) const {
    if (index < 0 || index >= static_cast<int>(m_sessions.size())) return nullptr;
    return m_sessions[index];
}

int TabHost::count() const {
    return static_cast<int>(m_sessions.size());
}

void TabHost::onCurrentChanged(int index) {
    if (index >= 0 && index < m_stackedWidget->count()) {
        m_stackedWidget->setCurrentIndex(index);
    }
}

void TabHost::onTabCloseRequested(int index) {
    removeTab(index, true);
}

void TabHost::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-tabsession-ptr")) {
        event->acceptProposedAction();
    }
}

void TabHost::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasFormat("application/x-tabsession-ptr")) {
        event->acceptProposedAction();
    }
}

void TabHost::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasFormat("application/x-tabsession-ptr")) {
        DetachableTabBar* sourceTabBar = reinterpret_cast<DetachableTabBar*>(event->mimeData()->data("application/x-tabsession-ptr").toLongLong());
        int sourceIndex = event->mimeData()->data("application/x-tabsession-index").toInt();

        TabHost* sourceHost = qobject_cast<TabHost*>(sourceTabBar->parent());
        if (sourceHost) {
            TabSession* session = sourceHost->getTab(sourceIndex);
            if (session) {
                int dropIndex = m_tabBar->tabAt(m_tabBar->mapFrom(this, event->position().toPoint()));
                if (dropIndex == -1 && event->position().y() < m_tabBar->height()) {
                    dropIndex = m_tabBar->count();
                }

                WindowManager::instance().moveTab(session, sourceHost, this, dropIndex);
                event->acceptProposedAction();
                return;
            }
        }
    }
    QWidget::dropEvent(event);
}
