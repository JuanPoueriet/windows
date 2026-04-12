#include "StatusBar.h"
#include <QHBoxLayout>
#include <QLabel>

StatusBar::StatusBar(QWidget* parent) : QWidget(parent) {
    setObjectName("status-bar");
    setFixedHeight(26);
    setupUi();
}

void StatusBar::setupUi() {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(14, 0, 14, 0);
    layout->setSpacing(14);

    auto createItem = [&](const QString& icon, const QString& text, bool success = false) {
        QWidget* item = new QWidget(this);
        item->setObjectName("status-item");
        QHBoxLayout* l = new QHBoxLayout(item);
        l->setContentsMargins(0, 0, 0, 0);
        l->setSpacing(5);
        QLabel* ic = new QLabel(item);
        ic->setPixmap(QIcon(QString(":/src/icons/%1.svg").arg(icon)).pixmap(10, 10));
        QLabel* t = new QLabel(text, item);
        if (success) t->setObjectName("status-ok");
        l->addWidget(ic);
        l->addWidget(t);
        return item;
    };

    layout->addWidget(createItem("shield-check", "Conectado", true));
    layout->addWidget(createItem("database", "atlas_prod"));
    layout->addWidget(createItem("clock", "12:45:00"));

    layout->addStretch();

    layout->addWidget(createItem("calendar", "Año fiscal 2025"));
    layout->addWidget(createItem("user", "Fernández"));
    layout->addWidget(createItem("shield-alt", "Enterprise v3.2.1"));
}
