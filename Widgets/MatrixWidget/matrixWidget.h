#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QTableWidget>
#include <QVector>
#include <QHeaderView>

class MatrixWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit MatrixWidget(QWidget *p = nullptr);

    void setMatrix(const QVector<QVector<int>> &matrix);

public slots:
    void generateCellValueChanged(int row, int col);

signals:
    void cellValueChanged(int row, int col, int weight);
    void headerDoubleClicked(int idx);
};

#endif // MATRIXWIDGET_H
