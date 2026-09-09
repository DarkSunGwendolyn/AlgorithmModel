#include "matrixWidget.h"

MatrixWidget::MatrixWidget(QWidget *p) : QTableWidget(p)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(
        this,
        &QTableWidget::cellChanged,
        this,
        &MatrixWidget::generateCellValueChanged
        );

    connect(
        verticalHeader(),
        &QHeaderView::sectionDoubleClicked,
        this,
        [this](int idx)
        {
            emit headerDoubleClicked(idx);
        });

    connect(
        horizontalHeader(),
        &QHeaderView::sectionDoubleClicked,
        this,
        [this](int idx)
        {
            emit headerDoubleClicked(idx);
        });
}

void MatrixWidget::setMatrix(const QVector<QVector<int>> &matrix)
{
    QSignalBlocker blocker(this);

    clear();

    setRowCount(matrix.size());
    setColumnCount(matrix.size());

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {

            QTableWidgetItem *item = new QTableWidgetItem(
                QString::number(matrix[i][j])
                );

            if (i == j)
            {
                item->setFlags(
                    item->flags() &
                    ~Qt::ItemIsEditable
                    );
            }

            setItem(i,
                    j,
                    item
                    );
        }
    }
}

void MatrixWidget::generateCellValueChanged(int row, int col)
{
    QTableWidgetItem *item = this->item(row, col);

    if (item == nullptr)
        return;

    bool ok = false;
    int value = item->text().toInt(&ok);

    if (!ok || value < 0)
        return;

    emit cellValueChanged(row, col, value);
}