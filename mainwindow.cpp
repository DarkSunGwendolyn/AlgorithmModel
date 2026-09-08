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

    connect(
        ui->findShortestPathsButton,
        &QPushButton::clicked,
        this,
        &MainWindow::findShortestPaths
        );

    initAlgorithmCombo();

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
}

void MainWindow::findShortestPath()
{
    int start = ui->fromVertexCombo->currentIndex();
    int finish = ui->toVertexCombo->currentIndex();
    Algorithm algorithm = static_cast<Algorithm>(
        ui->algorithmValueCombo->currentIndex());

    ShortestPathResult result = calculateShortestPath(
        algorithm,
        start,
        finish
        );

    if (result.path.isEmpty() || result.negativeCycle)
    {
        showNoPath();
        return;
    }

    showPath(result);
}

ShortestPathResult MainWindow::calculateShortestPath(
    Algorithm algorithm,
    int start,
    int finish)
{
    ShortestPathResult result;

    switch(algorithm)
    {

        case(Algorithm::Dijkstra):
        {
            DijkstraResult dijkstraResult =
                Dijkstra::findShortestPath(
                ui->graphWidget->getGraph(),
                start,
                finish
                );

            result.path = dijkstraResult.path;
            result.pathLen = dijkstraResult.pathLen;

            break;
        }

        case(Algorithm::Floyd):
        {
            FloydResult floydResult =
                Floyd::findShortestPath(
                    ui->graphWidget->getGraph(),
                    start,
                    finish
                );

            result.path = floydResult.path;
            result.pathLen = floydResult.pathLen;
            result.negativeCycle = floydResult.negativeCycle;

            break;
        }
    }

    return result;
}

void MainWindow::showNoPath()
{
    ui->pathValueLabel->setText("пути не существует");
    ui->pathLenValueLabel->setText("—");
}

void MainWindow::showPath(
    const ShortestPathResult &result)
{
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
        {0, 2, 0, 4, 0, 14, 0, 0, 24},
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

void MainWindow::initAlgorithmCombo()
{
    ui->algorithmValueCombo->addItem("Дейкстра");
    ui->algorithmValueCombo->addItem("Флойд");
}

void MainWindow::findShortestPaths()
{
    qDebug() << "start";
    FloydMatrixResult result =
        Floyd::findShortestPaths(ui->graphWidget->getGraph());

    if (result.negativeCycle)
    {
        showNegativeCycle();
        return;
    }

    QVector<PathTableRow> rows =
        PathMapper::map(result);

    ui->pathWidget->setPaths(rows);
}

void MainWindow::showNegativeCycle()
{
    ui->pathWidget->clearContents();
    ui->pathWidget->setRowCount(0);

    QMessageBox::warning(
        this,
        "Предупреждение",
        "В графе обнаружен отрицательный цикл.\n"
        "Кратчайшие пути не определены."
    );

}

MainWindow::~MainWindow()
{
    delete ui;
}
