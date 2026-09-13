#ifndef PACKETTABLEWIDGET_H
#define PACKETTABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QVector>

#include "packetTableRow.h"

class PacketTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit PacketTableWidget(QWidget *p);

    void addPacket(
        const PacketTableRow &row
        );

private:
    QString buildStringPath(const QVector<int> &path) const;
};

#endif // PACKETTABLEWIDGET_H
