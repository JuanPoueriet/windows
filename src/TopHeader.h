#pragma once

#include <QWidget>

class TopHeader : public QWidget {
    Q_OBJECT
public:
    explicit TopHeader(QWidget* parent = nullptr);

signals:
    void toggleSidebar();

private:
    void setupUi();
};
