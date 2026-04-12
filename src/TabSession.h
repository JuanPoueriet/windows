#pragma once

#include <QString>
#include <QIcon>
#include <QObject>

class TabView;

class TabSession : public QObject {
    Q_OBJECT
public:
    enum ModuleType {
        Dashboard,
        Invoicing,
        Inventory,
        Clients,
        Purchases,
        HR,
        Accounting,
        Reports,
        Analytics,
        Settings,
        Audit
    };
    Q_ENUM(ModuleType)

    explicit TabSession(const QString& title, QObject* parent = nullptr);

    QString title() const { return m_title; }
    void setTitle(const QString& title);

    QIcon icon() const { return m_icon; }
    void setIcon(const QIcon& icon);

    TabView* view() const { return m_view; }
    void setView(TabView* view);

    ModuleType moduleType() const { return m_moduleType; }
    void setModuleType(ModuleType type);

    bool isDirty() const { return m_isDirty; }
    void setDirty(bool dirty);

signals:
    void titleChanged(const QString& title);
    void iconChanged(const QIcon& icon);
    void moduleTypeChanged(ModuleType type);
    void dirtyChanged(bool dirty);

private:
    QString m_title;
    QIcon m_icon;
    TabView* m_view = nullptr;
    ModuleType m_moduleType = Dashboard;
    bool m_isDirty = false;
};
