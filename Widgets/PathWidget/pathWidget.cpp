#include "pathWidget.h"

PathWidget::PathWidget(QWidget *p) : QTableWidget(p)
{
    setColumnCount(4);

    setHorizontalHeaderLabels(
        {
            "Из",
            "В",
            "Путь",
            "Длина"
        });

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void PathWidget::setPaths(
    const QVector<PathTableRow> &rows)
{
    clearContents();
    setRowCount(rows.size());

    for (int i = 0; i < rows.size(); ++i)
    {
        const PathTableRow &row = rows[i];

        setItem(
            i,
            0,
            new QTableWidgetItem(
                QString::number(row.from + 1)
                )
            );

        setItem(
            i,
            1,
            new QTableWidgetItem(
                QString::number(row.to + 1)
                )
            );

        setItem(
            i,
            2,
            new QTableWidgetItem(
                buildStringPath(row.path)
                )
            );

        setItem(
            i,
            3,
            new QTableWidgetItem(
                QString::number(row.pathLen)
                )
            );
    }
}

QString PathWidget::buildStringPath(
    const QVector<int> &path) const
{
    QString stringPath;

    for (int i = 0; i < path.size(); ++i)
    {
        if (i > 0)
        {
            stringPath += "-";
        }

        stringPath += QString::number(path[i] + 1);
    }

    return stringPath;
}

void PathWidget::clear()
{
    setRowCount(0);
}
