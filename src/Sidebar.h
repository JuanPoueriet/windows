#pragma once

#include <QWidget>

class QVBoxLayout;

class Sidebar : public QWidget {
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);

    bool isCollapsed() const { return m_collapsed; }

public slots:
    void setCollapsed(bool collapsed);
    void toggleCollapsed();

private:
    void setupUi();
    QWidget* createNavItem(const QString& icon, const QString& label, const QString& badge = "", bool active = false);
    QWidget* createSectionLabel(const QString& label);

    bool m_collapsed = false;
    QVBoxLayout* m_mainLayout;
    QWidget* m_scrollContent;
    QVBoxLayout* m_scrollLayout;
};
