#pragma once

#include <QWidget>

class QTableWidget;

class DataTableWidget : public QWidget {
    Q_OBJECT
public:
    explicit DataTableWidget(const QString& title, const QString& subtitle, QWidget* parent = nullptr);

    void setHeaders(const QStringList& headers);
    void addRow(const QStringList& data, const QString& status = "");

private:
    void setupUi(const QString& title, const QString& subtitle);

    QTableWidget* m_table;
};
