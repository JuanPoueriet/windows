#pragma once

#include <QMainWindow>

class TabHost;
class Sidebar;
class TopHeader;
class StatusBar;

class AppWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit AppWindow(QWidget* parent = nullptr);
    TabHost* tabHost() const { return m_tabHost; }

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Sidebar* m_sidebar;
    TopHeader* m_header;
    StatusBar* m_statusBar;
    TabHost* m_tabHost;
};
