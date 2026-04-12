#include "TabHost.h"
#include "DetachableTabBar.h"
#include "TabSession.h"
#include "TabView.h"
#include "WindowManager.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPushButton>
#include <QIcon>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QDebug>

TabHost::TabHost(QWidget* parent) : QWidget(parent) {
    setObjectName("tab-host");
    setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QWidget* tabsBarWidget = new QWidget(this);
    tabsBarWidget->setObjectName("tabs-bar");
    tabsBarWidget->setFixedHeight(38);
    QHBoxLayout* tabsBarLayout = new QHBoxLayout(tabsBarWidget);
    tabsBarLayout->setContentsMargins(8, 0, 8, 0);
    tabsBarLayout->setSpacing(2);

    m_tabBar = new DetachableTabBar(tabsBarWidget);
    m_tabBar->setTabsClosable(true);
    m_tabBar->setMovable(true);
    m_tabBar->setExpanding(false);

    QPushButton* addTabButton = new QPushButton(QIcon(":/src/icons/plus.svg"), "", tabsBarWidget);
    addTabButton->setObjectName("newTabGlobal");
    addTabButton->setFixedSize(32, 32);

    tabsBarLayout->addWidget(m_tabBar);
    tabsBarLayout->addWidget(addTabButton);
    tabsBarLayout->addStretch();

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->setObjectName("mainContent");

    layout->addWidget(tabsBarWidget);
    layout->addWidget(m_stackedWidget);

    connect(m_tabBar, &QTabBar::currentChanged, this, &TabHost::onCurrentChanged);
    connect(m_tabBar, &QTabBar::tabCloseRequested, this, &TabHost::onTabCloseRequested);
    connect(addTabButton, &QPushButton::clicked, this, &TabHost::onAddTabRequested);
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

    connect(session->view(), &TabView::contentChanged, this, [this, session]() {
        session->setDirty(true);
    });

    connect(session, &TabSession::titleChanged, this, [this, session]() {
        updateTabDisplay(session);
    });

    connect(session, &TabSession::dirtyChanged, this, [this, session]() {
        updateTabDisplay(session);
    });

    connect(session, &TabSession::moduleTypeChanged, this, [this, session](TabSession::ModuleType type) {
        session->view()->setModuleType(type);
        updateTabDisplay(session);
    });

    session->view()->setModuleType(session->moduleType());
    updateTabDisplay(session);
}

void TabHost::removeTab(int index, bool deleteSession) {
    if (index < 0 || index >= static_cast<int>(m_sessions.size())) return;

    TabSession* session = m_sessions[index];

    session->view()->disconnect(this);
    session->disconnect(this);

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
        QWidget* current = m_stackedWidget->widget(index);
        if (current) {
            QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(current);
            current->setGraphicsEffect(effect);
            QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
            animation->setDuration(200); // Slightly faster for snappier feel
            animation->setStartValue(0.0);
            animation->setEndValue(1.0);
            animation->setEasingCurve(QEasingCurve::OutCubic);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        m_stackedWidget->setCurrentIndex(index);
    }
}

void TabHost::onTabCloseRequested(int index) {
    removeTab(index, true);
}

void TabHost::onAddTabRequested() {
    static int tabCount = 1;
    TabSession* session = new TabSession(QString("New Tab %1").arg(tabCount++), this);
    session->setModuleType(TabSession::Dashboard);
    TabView* view = new TabView();
    session->setView(view);
    addTab(session);
}

void TabHost::updateTabDisplay(TabSession* session) {
    static const QMap<TabSession::ModuleType, QString> moduleIcons = {
        {TabSession::Dashboard, "chart-line"},
        {TabSession::Invoicing, "file-invoice-dollar"},
        {TabSession::Inventory, "boxes-stacked"},
        {TabSession::Clients, "building-user"},
        {TabSession::Purchases, "truck-fast"},
        {TabSession::HR, "users"},
        {TabSession::Accounting, "calculator"},
        {TabSession::Reports, "chart-bar"},
        {TabSession::Analytics, "chart-line"},
        {TabSession::Settings, "gear"},
        {TabSession::Audit, "shield-check"}
    };

    for (int i = 0; i < static_cast<int>(m_sessions.size()); ++i) {
        if (m_sessions[i] == session) {
            QString displayText = session->title();
            if (session->isDirty()) {
                displayText = "* " + displayText;
            }
            m_tabBar->setTabText(i, displayText);
            m_tabBar->setTabIcon(i, QIcon(QString(":/src/icons/%1.svg").arg(moduleIcons.value(session->moduleType(), "circle"))));
            break;
        }
    }
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
