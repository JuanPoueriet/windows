#include "AppWindow.h"
#include "TabHost.h"
#include "Sidebar.h"
#include "TopHeader.h"
#include "StatusBar.h"
#include "WindowManager.h"
#include <QCloseEvent>
#include <QFile>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

AppWindow::AppWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_sidebar = new Sidebar(this);
    mainLayout->addWidget(m_sidebar);

    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    m_header = new TopHeader(this);
    m_tabHost = new TabHost(this);
    m_statusBar = new StatusBar(this);

    rightLayout->addWidget(m_header);
    rightLayout->addWidget(m_tabHost);
    rightLayout->addWidget(m_statusBar);

    mainLayout->addWidget(rightPanel);

    connect(m_header, &TopHeader::toggleSidebar, m_sidebar, &Sidebar::toggleCollapsed);

    resize(1200, 800);

    QFile file(":/src/StyleSheet.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
    }
}

void AppWindow::closeEvent(QCloseEvent* event) {
    WindowManager::instance().removeWindow(this);
    QMainWindow::closeEvent(event);
}
