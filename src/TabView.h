#pragma once

#include <QWidget>

class QTextEdit;

class TabView : public QWidget {
    Q_OBJECT
public:
    explicit TabView(QWidget* parent = nullptr);

    QString content() const;
    void setContent(const QString& content);

private:
    QTextEdit* m_textEdit;
};
