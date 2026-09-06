#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalBlocker>

#include "graphWidget.h"
#include "matrixWidget.h"
#include "dijkstra.h"

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

    void loadTestMatrix();

private slots:
    void findShortestPath();
};
#endif // MAINWINDOW_H
