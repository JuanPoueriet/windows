#include "DashboardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>

DashboardWidget::DashboardWidget(QWidget* parent) : QWidget(parent) {
    setupUi();
}

void DashboardWidget::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Module Header
    QWidget* header = new QWidget(this);
    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* titleGroup = new QWidget(header);
    QVBoxLayout* titleLayout = new QVBoxLayout(titleGroup);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(2);
    QLabel* title = new QLabel("Resumen ejecutivo", titleGroup);
    title->setObjectName("module-title");
    QLabel* subtitle = new QLabel("Vista consolidada del rendimiento del período", titleGroup);
    subtitle->setObjectName("module-subtitle");
    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);

    headerLayout->addWidget(titleGroup);
    headerLayout->addStretch();

    QPushButton* exportBtn = new QPushButton("Exportar", header);
    exportBtn->setIcon(QIcon(":/src/icons/plus.svg")); // Use appropriate icon
    headerLayout->addWidget(exportBtn);

    mainLayout->addWidget(header);

    // KPI Grid
    QGridLayout* kpiGrid = new QGridLayout();
    kpiGrid->setSpacing(12);

    kpiGrid->addWidget(createKpiCard("Ingresos", "$284,320", "+12.4%", "arrow-trend-up", "dollar-sign", "up"), 0, 0);
    kpiGrid->addWidget(createKpiCard("Cuentas por cobrar", "$47,840", "3 facturas vencidas", "triangle-exclamation", "file-invoice", "down"), 0, 1);
    kpiGrid->addWidget(createKpiCard("Órdenes de compra", "7", "2 en tránsito, 1 pendiente", "clock", "truck-fast", "neutral"), 0, 2);
    kpiGrid->addWidget(createKpiCard("Clientes activos", "42", "+4 nuevos este período", "arrow-trend-up", "building-user", "up"), 0, 3);

    mainLayout->addLayout(kpiGrid);

    // Lower panels
    QHBoxLayout* panelLayout = new QHBoxLayout();
    panelLayout->setSpacing(14);

    QFrame* chartPanel = new QFrame();
    chartPanel->setObjectName("panel");
    QVBoxLayout* chartV = new QVBoxLayout(chartPanel);
    QLabel* chartTitle = new QLabel("Ingresos vs Gastos", chartPanel);
    chartTitle->setObjectName("panel-title");
    chartV->addWidget(chartTitle);
    chartV->addStretch(); // Mock chart area

    QFrame* approvalPanel = new QFrame();
    approvalPanel->setObjectName("panel");
    approvalPanel->setFixedWidth(320);
    QVBoxLayout* appV = new QVBoxLayout(approvalPanel);
    QLabel* appTitle = new QLabel("Cola de aprobaciones", approvalPanel);
    appTitle->setObjectName("panel-title");
    appV->addWidget(appTitle);
    appV->addStretch();

    panelLayout->addWidget(chartPanel, 1);
    panelLayout->addWidget(approvalPanel);

    mainLayout->addLayout(panelLayout);
    mainLayout->addStretch();
}

QWidget* DashboardWidget::createKpiCard(const QString& label, const QString& value, const QString& trend, const QString& trendIcon, const QString& icon, const QString& trendType) {
    QFrame* card = new QFrame();
    card->setObjectName("kpi-card");
    QVBoxLayout* layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(10);

    QWidget* header = new QWidget(card);
    QHBoxLayout* hLayout = new QHBoxLayout(header);
    hLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* lbl = new QLabel(label, header);
    lbl->setObjectName("kpi-label");
    QLabel* ic = new QLabel(header);
    ic->setObjectName("kpi-icon");
    ic->setFixedSize(28, 28);
    ic->setPixmap(QIcon(QString(":/src/icons/%1.svg").arg(icon)).pixmap(14, 14));
    ic->setAlignment(Qt::AlignCenter);
    hLayout->addWidget(lbl);
    hLayout->addStretch();
    hLayout->addWidget(ic);

    QLabel* val = new QLabel(value, card);
    val->setObjectName("kpi-value");

    QWidget* trendWrap = new QWidget(card);
    QHBoxLayout* tLayout = new QHBoxLayout(trendWrap);
    tLayout->setContentsMargins(0, 0, 0, 0);
    tLayout->setSpacing(4);
    QLabel* tIc = new QLabel(trendWrap);
    tIc->setPixmap(QIcon(QString(":/src/icons/%1.svg").arg(trendIcon)).pixmap(10, 10));
    QLabel* tLbl = new QLabel(trend, trendWrap);
    tLbl->setObjectName("kpi-trend");
    tLbl->setProperty("type", trendType);
    tLayout->addWidget(tIc);
    tLayout->addWidget(tLbl);
    tLayout->addStretch();

    layout->addWidget(header);
    layout->addWidget(val);
    layout->addWidget(trendWrap);

    return card;
}
