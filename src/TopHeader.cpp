#include "TopHeader.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

TopHeader::TopHeader(QWidget* parent) : QWidget(parent) {
    setObjectName("top-header");
    setFixedHeight(52);
    setupUi();
}

void TopHeader::setupUi() {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 0, 16, 0);
    layout->setSpacing(12);

    QPushButton* toggleBtn = new QPushButton(this);
    toggleBtn->setObjectName("sidebar-toggle-btn");
    toggleBtn->setFixedSize(24, 24);
    toggleBtn->setIcon(QIcon(":/src/icons/chevron-left.svg"));
    connect(toggleBtn, &QPushButton::clicked, this, &TopHeader::toggleSidebar);

    QWidget* breadcrumb = new QWidget(this);
    breadcrumb->setObjectName("breadcrumb");
    QHBoxLayout* bcLayout = new QHBoxLayout(breadcrumb);
    bcLayout->setContentsMargins(0, 0, 0, 0);
    bcLayout->setSpacing(6);
    bcLayout->addWidget(new QLabel("ATLAS ERP"));
    QLabel* sep = new QLabel();
    sep->setObjectName("bc-sep");
    sep->setPixmap(QIcon(":/src/icons/chevron-right.svg").pixmap(8, 8));
    bcLayout->addWidget(sep);
    QLabel* current = new QLabel("Resumen");
    current->setObjectName("bc-current");
    bcLayout->addWidget(current);

    QWidget* searchWrap = new QWidget(this);
    searchWrap->setObjectName("search-wrap");
    searchWrap->setFixedWidth(380);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchWrap);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(0);

    QLineEdit* searchInput = new QLineEdit(searchWrap);
    searchInput->setObjectName("search-input");
    searchInput->setPlaceholderText("Buscar en todo ATLAS…");
    searchLayout->addWidget(searchInput);

    QWidget* actions = new QWidget(this);
    actions->setObjectName("header-actions");
    QHBoxLayout* actionsLayout = new QHBoxLayout(actions);
    actionsLayout->setContentsMargins(0, 0, 0, 0);
    actionsLayout->setSpacing(3);

    auto createHdrBtn = [&](const QString& icon) {
        QPushButton* btn = new QPushButton(actions);
        btn->setObjectName("hdr-btn");
        btn->setFixedSize(32, 32);
        btn->setIcon(QIcon(QString(":/src/icons/%1.svg").arg(icon)));
        return btn;
    };

    actionsLayout->addWidget(createHdrBtn("sun"));
    actionsLayout->addWidget(createHdrBtn("circle-question"));
    actionsLayout->addWidget(createHdrBtn("bell"));

    QWidget* hdrUser = new QWidget(this);
    hdrUser->setObjectName("hdr-user");
    QHBoxLayout* userLayout = new QHBoxLayout(hdrUser);
    userLayout->setContentsMargins(8, 4, 8, 4);
    userLayout->setSpacing(8);
    QLabel* uAv = new QLabel("LF");
    uAv->setObjectName("u-avatar-small");
    uAv->setFixedSize(26, 26);
    uAv->setAlignment(Qt::AlignCenter);
    QLabel* uName = new QLabel("Fernández");
    uName->setObjectName("hdr-user-name");
    userLayout->addWidget(uAv);
    userLayout->addWidget(uName);

    layout->addWidget(toggleBtn);
    layout->addWidget(breadcrumb);
    layout->addStretch();
    layout->addWidget(searchWrap);
    layout->addWidget(actions);
    layout->addWidget(hdrUser);
}
