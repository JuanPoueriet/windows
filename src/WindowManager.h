#pragma once

#include <QObject>
#include <vector>

class AppWindow;
class TabSession;
class TabHost;

class WindowManager : public QObject {
    Q_OBJECT
public:
    static WindowManager& instance();

    AppWindow* createWindow();
    void removeWindow(AppWindow* window);

    void moveTab(TabSession* session, TabHost* fromHost, TabHost* toHost, int toIndex = -1);
    void detachTab(TabSession* session, TabHost* fromHost, const QPoint& globalPos);

    void notifyTabHostEmpty(TabHost* host);

private:
    WindowManager() = default;
    std::vector<AppWindow*> m_windows;
};
