#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QElapsedTimer>
#include <QFileDialog>

#include "graphWidget.h"
#include "matrixWidget.h"
#include "pathWidget.h"
#include "dijkstra.h"
#include "floyd.h"
#include "shortestPathType.h"
#include "pathMapper.h"
#include "graphFile.h"
#include "routingAlgorithmProvider.h"
#include "packetRouter.h"
#include "packetFactory.h"
#include "packetTableRow.h"
#include "packetMapper.h"
#include "routingTableWidget.h"

struct ShortestPathResult
{
    QVector<int> path;
    int pathLen;
    bool negativeCycle = false;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    RoutingAlgorithmProvider algorithmProvider;

    PacketRouter packetRouter;

    void updateVertexCombos();
    void clearShortestPathResult();

    void initAlgorithmCombo();

    void loadTestMatrix();

    ShortestPathResult calculateShortestPath(
        ShortestPathType algorithm,
        int start,
        int finish
        );

    void showNoPath();

    void showPath(const ShortestPathResult &result);

    void showNegativeCycle();

    void showExecutionTime(
        qint64 dijkstraTime,
        qint64 floydTime
        );

    void processPacketResult(
        const QVector<Packet> &packets,
        PacketStatus status);

    void updateRoutingTableWidget();



private slots:
    void findShortestPath();
    void findShortestPaths();

    void saveGraph();
    void loadGraph();

    void setRoutingAlgorithm();

    void routePacket();
};
#endif // MAINWINDOW_H
