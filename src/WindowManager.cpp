#include "WindowManager.h"
#include "AppWindow.h"
#include "TabHost.h"
#include "TabSession.h"
#include <algorithm>
#include <QApplication>
#include <QScreen>
#include <QDebug>

WindowManager& WindowManager::instance() {
    static WindowManager manager;
    return manager;
}

AppWindow* WindowManager::createWindow() {
    AppWindow* window = new AppWindow();
    m_windows.push_back(window);
    window->show();
    return window;
}

void WindowManager::removeWindow(AppWindow* window) {
    auto it = std::find(m_windows.begin(), m_windows.end(), window);
    if (it != m_windows.end()) {
        m_windows.erase(it);
    }
    if (m_windows.empty()) {
        QApplication::quit();
    }
}

void WindowManager::moveTab(TabSession* session, TabHost* fromHost, TabHost* toHost, int toIndex) {
    if (!session || !fromHost || !toHost) return;

    int fromIndex = -1;
    for (int i = 0; i < fromHost->count(); ++i) {
        if (fromHost->getTab(i) == session) {
            fromIndex = i;
            break;
        }
    }

    if (fromIndex == -1) return;

    // Prevent deletion of host/window while moving if it's the last tab
    // We move first, then remove from source.
    fromHost->removeTab(fromIndex, false);

    if (toIndex == -1) {
        toHost->addTab(session);
    } else {
        toHost->insertTab(toIndex, session);
    }
}

void WindowManager::detachTab(TabSession* session, TabHost* fromHost, const QPoint& globalPos) {
    int fromIndex = -1;
    for (int i = 0; i < fromHost->count(); ++i) {
        if (fromHost->getTab(i) == session) {
            fromIndex = i;
            break;
        }
    }
    if (fromIndex == -1) return;

    fromHost->removeTab(fromIndex, false);

    AppWindow* newWindow = createWindow();
    newWindow->tabHost()->addTab(session);
    newWindow->move(globalPos);
}

void WindowManager::notifyTabHostEmpty(TabHost* host) {
    AppWindow* window = qobject_cast<AppWindow*>(host->window());
    if (window) {
        // We use deleteLater to avoid issues if we are in a middle of some event
        window->deleteLater();
        removeWindow(window);
    }
}
