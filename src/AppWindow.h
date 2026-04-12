#pragma once

#include <QMainWindow>

class TabHost;

class AppWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit AppWindow(QWidget* parent = nullptr);
    TabHost* tabHost() const { return m_tabHost; }

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    TabHost* m_tabHost;
};
