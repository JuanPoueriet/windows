#include "AppWindow.h"
#include "TabHost.h"
#include "WindowManager.h"
#include <QCloseEvent>
#include <QFile>
#include <QApplication>

AppWindow::AppWindow(QWidget* parent) : QMainWindow(parent) {
    m_tabHost = new TabHost(this);
    setCentralWidget(m_tabHost);
    resize(800, 600);

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
