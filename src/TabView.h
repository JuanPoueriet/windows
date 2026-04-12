#pragma once

#include <QWidget>
#include "TabSession.h"

class QStackedWidget;
class DashboardWidget;
class DataTableWidget;

class TabView : public QWidget {
    Q_OBJECT
public:
    explicit TabView(QWidget* parent = nullptr);

    void setModuleType(TabSession::ModuleType type);

signals:
    void contentChanged();

private:
    void setupUi();

    QStackedWidget* m_stack;
    DashboardWidget* m_dashboard;
    DataTableWidget* m_inventory;
    DataTableWidget* m_clients;
    DataTableWidget* m_invoicing;
};
