#include "routingTableWidget.h"

RoutingTableWidget::RoutingTableWidget(QWidget *p) : QTableWidget(p)
{
    setColumnCount(2);

    setHorizontalHeaderLabels(
        {
            "Узел",
            "Расстояние"
        });

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void RoutingTableWidget::setRoutingTable(
    const RoutingTable &table
    )
{
    clear();

    for (int i = 0; i < table.distances.size(); ++i)
    {
        int distance = table.distances[i];

        if (distance == -1)
        {
            continue;
        }

        int rowIndex = rowCount();

        insertRow(rowIndex);

        setItem(
            rowIndex,
            0,
            new QTableWidgetItem(
                QString::number(i + 1)
                )
            );

        setItem(
            rowIndex,
            1,
            new QTableWidgetItem(
                QString::number(distance)
                )
            );
    }
}

void RoutingTableWidget::clear()
{
    setRowCount(0);
}
