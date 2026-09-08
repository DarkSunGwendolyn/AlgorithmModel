#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QVector>

#include "pathTableRow.h"

class PathWidget : public QTableWidget
{
    Q_OBJECT

public:

    explicit PathWidget(QWidget *p = nullptr);

    void setPaths(
        const QVector<PathTableRow> &rows
        );

private:
    QString buildStringPath(const QVector<int> &path) const;
};

#endif // PATHWIDGET_H
