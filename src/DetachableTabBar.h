#pragma once

#include <QTabBar>
#include <QPoint>

class DetachableTabBar : public QTabBar {
    Q_OBJECT
public:
    explicit DetachableTabBar(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    QPoint m_dragStartPosition;
};
