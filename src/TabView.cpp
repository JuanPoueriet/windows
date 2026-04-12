#include "TabView.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>

TabView::TabView(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    QLabel* label = new QLabel("Tab Content - State is preserved here:", this);
    label->setStyleSheet("font-weight: bold; color: #4a9eff;");
    layout->addWidget(label);

    m_textEdit = new QTextEdit(this);
    layout->addWidget(m_textEdit);
}

QString TabView::content() const {
    return m_textEdit->toPlainText();
}

void TabView::setContent(const QString& content) {
    m_textEdit->setPlainText(content);
}
