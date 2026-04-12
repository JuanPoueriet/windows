#pragma once

#include <QWidget>

class DashboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit DashboardWidget(QWidget* parent = nullptr);

private:
    void setupUi();
    QWidget* createKpiCard(const QString& label, const QString& value, const QString& trend, const QString& trendIcon, const QString& icon, const QString& trendType);
};
