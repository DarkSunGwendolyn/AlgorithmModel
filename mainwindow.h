#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QElapsedTimer>

#include "graphWidget.h"
#include "matrixWidget.h"
#include "pathWidget.h"

#include "dijkstra.h"
#include "floyd.h"
#include "algorithm.h"

#include "pathMapper.h"

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

    void updateVertexCombos();
    void clearShortestPathResult();

    void initAlgorithmCombo();

    void loadTestMatrix();

    ShortestPathResult calculateShortestPath(
        Algorithm algorithm,
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



private slots:
    void findShortestPath();
    void findShortestPaths();
};
#endif // MAINWINDOW_H
