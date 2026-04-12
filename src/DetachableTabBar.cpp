#include "DetachableTabBar.h"
#include "TabHost.h"
#include "TabSession.h"
#include "WindowManager.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QInputDialog>

DetachableTabBar::DetachableTabBar(QWidget* parent) : QTabBar(parent) {
    setAcceptDrops(true);
    setMovable(true);
}

void DetachableTabBar::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    } else if (event->button() == Qt::MiddleButton) {
        int index = tabAt(event->pos());
        if (index != -1) {
            emit tabCloseRequested(index);
        }
    }
    QTabBar::mousePressEvent(event);
}

void DetachableTabBar::mouseDoubleClickEvent(QMouseEvent* event) {
    int index = tabAt(event->pos());
    if (index != -1) {
        TabHost* host = qobject_cast<TabHost*>(parent());
        if (host) {
            TabSession* session = host->getTab(index);
            if (session) {
                bool ok;
                QString newTitle = QInputDialog::getText(this, tr("Rename Tab"),
                                                         tr("New title:"), QLineEdit::Normal,
                                                         session->title(), &ok);
                if (ok && !newTitle.isEmpty()) {
                    session->setTitle(newTitle);
                }
            }
        }
    }
    QTabBar::mouseDoubleClickEvent(event);
}

void DetachableTabBar::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }
    if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }

    int tabIndex = tabAt(event->pos());
    if (tabIndex == -1) {
        return;
    }

    TabHost* host = qobject_cast<TabHost*>(parent());
    if (!host) return;
    TabSession* session = host->getTab(tabIndex);

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();

    mimeData->setData("application/x-tabsession-ptr", QByteArray::number(reinterpret_cast<quintptr>(this)));
    mimeData->setData("application/x-tabsession-index", QByteArray::number(tabIndex));

    drag->setMimeData(mimeData);
    drag->setPixmap(grab(tabRect(tabIndex)));

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);

    if (dropAction == Qt::IgnoreAction) {
        WindowManager::instance().detachTab(session, host, QCursor::pos());
    }
}

void DetachableTabBar::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-tabsession-ptr")) {
        event->acceptProposedAction();
    }
}

void DetachableTabBar::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasFormat("application/x-tabsession-ptr")) {
        event->acceptProposedAction();
    }
}
