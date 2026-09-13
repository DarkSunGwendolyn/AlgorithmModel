#include "packetTableWidget.h"

PacketTableWidget::PacketTableWidget(QWidget *p) : QTableWidget(p)
{
    setColumnCount(6);
    setHorizontalHeaderLabels(
        {
            "№",
            "Откуда",
            "Куда",
            "Маршрут",
            "Размер",
            "Статус"
        });

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void PacketTableWidget::addPacket(
    const PacketTableRow &row)
{
    int rowIndex = rowCount();
    insertRow(rowIndex);

    setItem(
        rowIndex,
        0,
        new QTableWidgetItem(
            QString::number(row.number)
            )
        );

    setItem(
        rowIndex,
        1,
        new QTableWidgetItem(
            QString::number(row.source + 1)
            )
        );

    setItem(
        rowIndex,
        2,
        new QTableWidgetItem(
            QString::number(row.destination + 1)
            )
        );

    setItem(
        rowIndex,
        3,
        new QTableWidgetItem(
            buildStringPath(row.path)
            )
        );

    setItem(
        rowIndex,
        4,
        new QTableWidgetItem(
            QString::number(row.size)
            )
        );

    QTableWidgetItem *statusItem =
        new QTableWidgetItem(
            row.status == PacketStatus::Delivered
                ? "доставлен"
                : "потерян"
            );

    statusItem->setForeground(
        row.status == PacketStatus::Delivered
            ? Qt::green
            : Qt::red
        );

    setItem(
        rowIndex,
        5,
        statusItem
        );
}

QString PacketTableWidget::buildStringPath(
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
