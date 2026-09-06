#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->graphWidget,
        &GraphWidget::graphChanged,
        this,
        [this]()
        {
            ui->matrixWidget->setMatrix(
                ui->graphWidget->getAdjacencyMatrix()
                );

            updateVertexCombos();
            clearShortestPathResult();
        });

    connect(
        ui->vertexCountValueSpin,
        &QSpinBox::valueChanged,
        ui->graphWidget,
        &GraphWidget::setVertexCount
        );

    connect(
        ui->matrixWidget,
        &MatrixWidget::cellValueChanged,
        ui->graphWidget,
        &GraphWidget::setMatrixValue
        );

    connect(
        ui->graphWidget,
        &GraphWidget::vertexCountChanged,
        this,
        [this](int count)
        {
            QSignalBlocker blocker(ui->vertexCountValueSpin);
            ui->vertexCountValueSpin->setValue(count);
        }
        );

    connect(
        ui->findShortestPathButton,
        &QPushButton::clicked,
        this,
        &MainWindow::findShortestPath
        );

    loadTestMatrix();
}

void MainWindow::updateVertexCombos()
{
    int count = ui->graphWidget->getAdjacencyMatrix().size();

    ui->fromVertexCombo->clear();
    ui->toVertexCombo->clear();

    for (int i = 0; i < count; ++i)
    {
        ui->fromVertexCombo->addItem(QString::number(i+1));
        ui->toVertexCombo->addItem(QString::number(i+1));
    }

    ui->fromVertexCombo->setCurrentIndex(0);
    ui->toVertexCombo->setCurrentIndex(0);
}

void MainWindow::findShortestPath()
{
    int start = ui->fromVertexCombo->currentIndex();
    int finish = ui->toVertexCombo->currentIndex();

    DijkstraResult result = Dijkstra::findShortestPath(
        ui->graphWidget->getGraph(),
        start,
        finish
        );

    if (result.path.isEmpty() || result.pathLen == 0)
    {
        ui->pathValueLabel->setText("пути не существует");
        ui->pathLenValueLabel->setText("—");

        return;
    }

    ui->graphWidget->highlightPath(result.path);

    QString path;

    for (int i = 0; i < result.path.size(); ++i)
    {
        if (i > 0)
        {
            path += "-";
        }

        path += QString::number(result.path[i] + 1);
    }

    ui->pathValueLabel->setText(path);
    ui->pathLenValueLabel->setText(
        QString::number(result.pathLen)
        );
}

void MainWindow::clearShortestPathResult()
{
    ui->pathValueLabel->setText("");
    ui->pathLenValueLabel->setText("");
}

void MainWindow::loadTestMatrix()
{
    QVector<QVector<int>> testMatrix =
    {
        {0, 10, 0, 0, 0, 0, 3, 6, 12},
        {10, 0, 18, 0, 0, 0, 2, 0, 13},
        {0, 18, 0, 25, 0, 20, 0, 0, 7},
        {0, 0, 25, 0, 5, 16, 4, 0, 0},
        {0, 0, 0, 5, 0, 10, 0, 0, 0},
        {0, 0, 20, 0, 10, 0, 14, 15, 9},
        {0, 2, 0, 0, 4, 0, 14, 0, 0, 24},
        {6, 0, 0, 0, 23, 15, 0, 0, 5},
        {2, 13, 0, 0, 0, 9, 24, 5, 0}
    };

    ui->graphWidget->setVertexCount(testMatrix.size());

    for (int i = 0; i < testMatrix.size(); ++i)
    {
        for (int j = 0; j < testMatrix[i].size(); ++j)
        {
            ui->graphWidget->setMatrixValue(
                i,
                j,
                testMatrix[i][j]
                );
        }
    }

    ui->matrixWidget->setMatrix(testMatrix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
