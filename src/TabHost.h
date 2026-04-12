#pragma once

#include <QWidget>
#include <vector>

class DetachableTabBar;
class QStackedWidget;
class TabSession;

class TabHost : public QWidget {
    Q_OBJECT
public:
    explicit TabHost(QWidget* parent = nullptr);
    ~TabHost();

    void addTab(TabSession* session);
    void insertTab(int index, TabSession* session);
    void removeTab(int index, bool deleteSession = false);
    TabSession* getTab(int index) const;
    int count() const;

    DetachableTabBar* tabBar() const { return m_tabBar; }

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onCurrentChanged(int index);
    void onTabCloseRequested(int index);

private:
    DetachableTabBar* m_tabBar;
    QStackedWidget* m_stackedWidget;
    std::vector<TabSession*> m_sessions;
};
