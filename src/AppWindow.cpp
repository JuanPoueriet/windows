#include "AppWindow.h"
#include "TabHost.h"
#include "WindowManager.h"
#include <QCloseEvent>

AppWindow::AppWindow(QWidget* parent) : QMainWindow(parent) {
    m_tabHost = new TabHost(this);
    setCentralWidget(m_tabHost);
    resize(800, 600);
}

void AppWindow::closeEvent(QCloseEvent* event) {
    WindowManager::instance().removeWindow(this);
    QMainWindow::closeEvent(event);
}
