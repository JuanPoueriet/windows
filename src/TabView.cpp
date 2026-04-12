#include "TabView.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>

TabView::TabView(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Tab Content - State is preserved here:"));
    m_textEdit = new QTextEdit(this);
    layout->addWidget(m_textEdit);
}

QString TabView::content() const {
    return m_textEdit->toPlainText();
}

void TabView::setContent(const QString& content) {
    m_textEdit->setPlainText(content);
}
