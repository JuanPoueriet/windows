#pragma once

#include <QString>
#include <QIcon>
#include <QObject>

class TabView;

class TabSession : public QObject {
    Q_OBJECT
public:
    explicit TabSession(const QString& title, QObject* parent = nullptr);

    QString title() const { return m_title; }
    void setTitle(const QString& title);

    QIcon icon() const { return m_icon; }
    void setIcon(const QIcon& icon);

    TabView* view() const { return m_view; }
    void setView(TabView* view);

    bool isDirty() const { return m_isDirty; }
    void setDirty(bool dirty);

signals:
    void titleChanged(const QString& title);
    void iconChanged(const QIcon& icon);
    void dirtyChanged(bool dirty);

private:
    QString m_title;
    QIcon m_icon;
    TabView* m_view = nullptr;
    bool m_isDirty = false;
};
