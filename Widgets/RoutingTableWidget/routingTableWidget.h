#ifndef ROUTINGTABLEWIDGET_H
#define ROUTINGTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>

#include "routingTable.h"


class RoutingTableWidget : public QTableWidget
{
public:
    explicit RoutingTableWidget(QWidget *p);

    void setRoutingTable(
        const RoutingTable &table
        );

    void clear();
};

#endif // ROUTINGTABLEWIDGET_H
