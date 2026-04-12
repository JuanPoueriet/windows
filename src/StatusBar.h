#pragma once

#include <QWidget>

class StatusBar : public QWidget {
    Q_OBJECT
public:
    explicit StatusBar(QWidget* parent = nullptr);

private:
    void setupUi();
};
