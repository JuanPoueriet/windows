#include "TabView.h"
#include "DashboardWidget.h"
#include "DataTableWidget.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

TabView::TabView(QWidget* parent) : QWidget(parent) {
    setupUi();
}

void TabView::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_stack = new QStackedWidget(this);
    layout->addWidget(m_stack);

    m_dashboard = new DashboardWidget(this);
    m_stack->addWidget(m_dashboard);

    m_invoicing = new DataTableWidget("Facturación", "Emisión y gestión de comprobantes fiscales", this);
    m_invoicing->setHeaders({"N°", "Cliente", "Total", "Estado"});
    m_invoicing->addRow({"#2025-046", "Grupo Nexus", "$3,849.98", "Pagada"});
    m_invoicing->addRow({"#2025-047", "Digital Mind", "$1,299.99", "Pendiente"});
    m_stack->addWidget(m_invoicing);

    m_inventory = new DataTableWidget("Inventario", "Control de existencias y gestión de productos", this);
    m_inventory->setHeaders({"Producto", "SKU", "Categoría", "Stock", "Precio"});
    m_inventory->addRow({"Laptop Dell XPS 15", "DELL-XPS-001", "Cómputo", "24", "$1,499.99"});
    m_inventory->addRow({"Monitor LG 27\" 4K", "LG-MON-27K", "Pantallas", "2", "$649.00"});
    m_stack->addWidget(m_inventory);

    m_clients = new DataTableWidget("CRM / Clientes", "Gestión de cartera y relaciones comerciales", this);
    m_clients->setHeaders({"Empresa", "Email", "Teléfono", "Segmento", "Facturado"});
    m_clients->addRow({"Grupo Nexus S.A.", "contacto@nexus.mx", "+52 55 1234-5678", "Enterprise", "$127,450"});
    m_stack->addWidget(m_clients);
}

void TabView::setModuleType(TabSession::ModuleType type) {
    switch (type) {
        case TabSession::Dashboard: m_stack->setCurrentWidget(m_dashboard); break;
        case TabSession::Invoicing: m_stack->setCurrentWidget(m_invoicing); break;
        case TabSession::Inventory: m_stack->setCurrentWidget(m_inventory); break;
        case TabSession::Clients: m_stack->setCurrentWidget(m_clients); break;
        default: m_stack->setCurrentIndex(0); break;
    }
}
