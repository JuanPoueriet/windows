#include "DataTableWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>

DataTableWidget::DataTableWidget(const QString& title, const QString& subtitle, QWidget* parent) : QWidget(parent) {
    setupUi(title, subtitle);
}

void DataTableWidget::setupUi(const QString& titleStr, const QString& subtitleStr) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(18);

    QWidget* header = new QWidget(this);
    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* titleGroup = new QWidget(header);
    QVBoxLayout* titleLayout = new QVBoxLayout(titleGroup);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(2);
    QLabel* title = new QLabel(titleStr, titleGroup);
    title->setObjectName("module-title");
    QLabel* subtitle = new QLabel(subtitleStr, titleGroup);
    subtitle->setObjectName("module-subtitle");
    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);

    headerLayout->addWidget(titleGroup);
    headerLayout->addStretch();

    QPushButton* addBtn = new QPushButton("Nuevo", header);
    addBtn->setIcon(QIcon(":/src/icons/plus.svg"));
    headerLayout->addWidget(addBtn);

    mainLayout->addWidget(header);

    QFrame* panel = new QFrame(this);
    panel->setObjectName("panel");
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->setContentsMargins(0, 0, 0, 0);
    panelLayout->setSpacing(0);

    m_table = new QTableWidget(panel);
    m_table->setFrameShape(QFrame::NoFrame);
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    m_table->verticalHeader()->setVisible(false);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setAlternatingRowColors(false);
    m_table->setShowGrid(false);

    panelLayout->addWidget(m_table);

    mainLayout->addWidget(panel);
}

void DataTableWidget::setHeaders(const QStringList& headers) {
    m_table->setColumnCount(headers.size());
    m_table->setHorizontalHeaderLabels(headers);
}

void DataTableWidget::addRow(const QStringList& data, const QString& status) {
    int row = m_table->rowCount();
    m_table->insertRow(row);
    for (int i = 0; i < data.size(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(data[i]);
        m_table->setItem(row, i, item);
    }
    if (!status.isEmpty()) {
        // Status handling would be more complex with custom cell widgets
    }
}
