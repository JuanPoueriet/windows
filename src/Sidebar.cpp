#include "Sidebar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>

Sidebar::Sidebar(QWidget* parent) : QWidget(parent) {
    setObjectName("sidebar");
    setFixedWidth(240);
    setupUi();
}

void Sidebar::setupUi() {
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    // Brand row
    QWidget* brandRow = new QWidget(this);
    brandRow->setObjectName("sidebar-brand");
    brandRow->setFixedHeight(52);
    QHBoxLayout* brandLayout = new QHBoxLayout(brandRow);
    brandLayout->setContentsMargins(14, 0, 14, 0);
    brandLayout->setSpacing(9);

    QLabel* brandIcon = new QLabel(brandRow);
    brandIcon->setObjectName("brand-icon");
    brandIcon->setFixedSize(26, 26);
    brandIcon->setPixmap(QIcon(":/src/icons/layer-group.svg").pixmap(16, 16));
    brandIcon->setAlignment(Qt::AlignCenter);

    QLabel* brandName = new QLabel("ATLAS", brandRow);
    brandName->setObjectName("brand-name");

    QLabel* brandVer = new QLabel("v3.2", brandRow);
    brandVer->setObjectName("brand-ver");

    brandLayout->addWidget(brandIcon);
    brandLayout->addWidget(brandName);
    brandLayout->addWidget(brandVer);
    brandLayout->addStretch();

    m_mainLayout->addWidget(brandRow);

    // Org selector
    QWidget* orgSelector = new QWidget(this);
    orgSelector->setObjectName("sidebar-org");
    QHBoxLayout* orgLayout = new QHBoxLayout(orgSelector);
    orgLayout->setContentsMargins(12, 8, 12, 8);
    orgLayout->setSpacing(8);

    QLabel* orgAvatar = new QLabel("GN", orgSelector);
    orgAvatar->setObjectName("org-avatar");
    orgAvatar->setFixedSize(22, 22);
    orgAvatar->setAlignment(Qt::AlignCenter);

    QWidget* orgInfo = new QWidget(orgSelector);
    QVBoxLayout* orgInfoLayout = new QVBoxLayout(orgInfo);
    orgInfoLayout->setContentsMargins(0, 0, 0, 0);
    orgInfoLayout->setSpacing(0);
    QLabel* orgName = new QLabel("Grupo Nexus S.A.", orgInfo);
    orgName->setObjectName("org-name");
    QLabel* orgType = new QLabel("Enterprise · MX", orgInfo);
    orgType->setObjectName("org-type");
    orgInfoLayout->addWidget(orgName);
    orgInfoLayout->addWidget(orgType);

    orgLayout->addWidget(orgAvatar);
    orgLayout->addWidget(orgInfo);
    orgLayout->addStretch();

    m_mainLayout->addWidget(orgSelector);

    // Scroll Area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("sidebar-scroll");
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    m_scrollContent = new QWidget();
    m_scrollLayout = new QVBoxLayout(m_scrollContent);
    m_scrollLayout->setContentsMargins(8, 8, 8, 8);
    m_scrollLayout->setSpacing(2);

    m_scrollLayout->addWidget(createSectionLabel("Favoritos"));
    m_scrollLayout->addWidget(createNavItem("file-invoice-dollar", "Facturación", "3"));
    m_scrollLayout->addWidget(createNavItem("boxes-stacked", "Inventario", "!", false));

    QFrame* divider1 = new QFrame();
    divider1->setObjectName("nav-divider");
    divider1->setFrameShape(QFrame::HLine);
    m_scrollLayout->addWidget(divider1);

    m_scrollLayout->addWidget(createSectionLabel("General"));
    m_scrollLayout->addWidget(createNavItem("chart-line", "Resumen ejecutivo", "Hoy", true));

    m_scrollLayout->addWidget(createSectionLabel("Operaciones"));
    m_scrollLayout->addWidget(createNavItem("building-user", "CRM / Clientes"));
    m_scrollLayout->addWidget(createNavItem("truck-fast", "Compras"));
    m_scrollLayout->addWidget(createNavItem("users", "Recursos Humanos"));
    m_scrollLayout->addWidget(createNavItem("calculator", "Contabilidad"));

    m_scrollLayout->addWidget(createSectionLabel("Análisis"));
    m_scrollLayout->addWidget(createNavItem("chart-bar", "Reportes"));
    m_scrollLayout->addWidget(createNavItem("chart-line", "Analytics"));

    m_scrollLayout->addStretch();

    scrollArea->setWidget(m_scrollContent);
    m_mainLayout->addWidget(scrollArea);

    // User row
    QWidget* userRow = new QWidget(this);
    userRow->setObjectName("sidebar-user");
    QHBoxLayout* userLayout = new QHBoxLayout(userRow);
    userLayout->setContentsMargins(12, 10, 12, 10);
    userLayout->setSpacing(8);

    QLabel* uAvatar = new QLabel("LF", userRow);
    uAvatar->setObjectName("u-avatar");
    uAvatar->setFixedSize(28, 28);
    uAvatar->setAlignment(Qt::AlignCenter);

    QWidget* uInfo = new QWidget(userRow);
    QVBoxLayout* uInfoLayout = new QVBoxLayout(uInfo);
    uInfoLayout->setContentsMargins(0, 0, 0, 0);
    uInfoLayout->setSpacing(0);
    QLabel* uName = new QLabel("Lic. Fernández", uInfo);
    uName->setObjectName("u-name");
    QLabel* uRole = new QLabel("Administrador", uInfo);
    uRole->setObjectName("u-role");
    uInfoLayout->addWidget(uName);
    uInfoLayout->addWidget(uRole);

    QWidget* uDot = new QWidget(userRow);
    uDot->setObjectName("u-dot");
    uDot->setFixedSize(7, 7);

    userLayout->addWidget(uAvatar);
    userLayout->addWidget(uInfo);
    userLayout->addStretch();
    userLayout->addWidget(uDot);

    m_mainLayout->addWidget(userRow);
}

QWidget* Sidebar::createSectionLabel(const QString& label) {
    QLabel* lbl = new QLabel(label);
    lbl->setObjectName("sidebar-section-label");
    return lbl;
}

QWidget* Sidebar::createNavItem(const QString& icon, const QString& label, const QString& badge, bool active) {
    QWidget* item = new QWidget();
    item->setObjectName("nav-item");
    if (active) item->setProperty("active", true);

    QHBoxLayout* layout = new QHBoxLayout(item);
    layout->setContentsMargins(10, 7, 10, 7);
    layout->setSpacing(9);

    QLabel* iconLbl = new QLabel(item);
    iconLbl->setFixedSize(16, 16);
    iconLbl->setPixmap(QIcon(QString(":/src/icons/%1.svg").arg(icon)).pixmap(14, 14));
    iconLbl->setAlignment(Qt::AlignCenter);

    QLabel* textLbl = new QLabel(label, item);
    textLbl->setObjectName("nav-text");

    layout->addWidget(iconLbl);
    layout->addWidget(textLbl);

    if (!badge.isEmpty()) {
        QLabel* badgeLbl = new QLabel(badge, item);
        badgeLbl->setObjectName("nav-badge");
        if (badge == "!") badgeLbl->setProperty("type", "warn");
        else if (badge == "Hoy") badgeLbl->setProperty("type", "muted");
        layout->addWidget(badgeLbl);
    } else {
        layout->addStretch();
    }

    return item;
}

void Sidebar::setCollapsed(bool collapsed) {
    m_collapsed = collapsed;
    setFixedWidth(m_collapsed ? 52 : 240);
    // In a real impl we would hide labels, but QSS can also handle some of it or we do it here
    for (auto label : findChildren<QLabel*>()) {
        if (label->objectName() == "brand-name" || label->objectName() == "brand-ver" ||
            label->objectName() == "nav-text" || label->objectName() == "nav-badge" ||
            label->objectName() == "org-name" || label->objectName() == "org-type" ||
            label->objectName() == "u-name" || label->objectName() == "u-role" ||
            label->objectName() == "sidebar-section-label") {
            label->setVisible(!collapsed);
        }
    }
    findChild<QWidget*>("u-dot")->setVisible(!collapsed);
}

void Sidebar::toggleCollapsed() {
    setCollapsed(!m_collapsed);
}
