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
        ui->matrixWidget,
        &MatrixWidget::headerDoubleClicked,
        ui->graphWidget,
        &GraphWidget::deleteVertexById
        );

    connect(
        ui->graphWidget,
        &GraphWidget::vertexCountChanged,
        this,
        [this](int count)
        {
            QSignalBlocker blocker(ui->vertexCountValueSpin);
            ui->vertexCountValueSpin->setValue(count);
        });

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

    connect(
        ui->showTimeCheck,
        &QCheckBox::toggled,
        ui->timePanel,
        &QFrame::setVisible
        );

    connect(
        ui->actionSave,
        &QAction::triggered,
        this,
        &MainWindow::saveGraph
        );

    connect(
        ui->actionLoad,
        &QAction::triggered,
        this,
        &MainWindow::loadGraph
        );

    connect(
        ui->routingPageButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->algorithmStackedWidget->setCurrentWidget(ui->routingPage);
        });

    connect(
        ui->shortestPathPageButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            ui->algorithmStackedWidget->setCurrentWidget(ui->shortestPathPage);
        });

    connect(
        ui->routingAlgorithmCombo,
        &QComboBox::currentIndexChanged,
        this,
        &MainWindow::setRoutingAlgorithm
        );

    connect(
        ui->sendPacketButton,
        &QPushButton::clicked,
        this,
        &MainWindow::routePacket
        );

    initAlgorithmCombo();
    setRoutingAlgorithm();

    //loadTestMatrix();

    ui->timePanel->hide();
}

void MainWindow::updateVertexCombos()
{
    int count = ui->graphWidget->getAdjacencyMatrix().size();

    ui->fromVertexCombo->clear();
    ui->toVertexCombo->clear();

    ui->fromRoutingCombo->clear();
    ui->toRoutingCombo->clear();

    for (int i = 0; i < count; ++i)
    {
        ui->fromVertexCombo->addItem(QString::number(i+1));
        ui->toVertexCombo->addItem(QString::number(i+1));

        ui->fromRoutingCombo->addItem(QString::number(i+1));
        ui->toRoutingCombo->addItem(QString::number(i+1));
    }
}

void MainWindow::findShortestPath()
{
    if (ui->fromVertexCombo->count() == 0 ||
        ui->toVertexCombo->count() == 0)
    {
        QMessageBox::warning(
            this,
            "Отсутствуют вершины",
            "В графе нет вершин."
            );

        return;
    }

    int start = ui->fromVertexCombo->currentIndex();
    int finish = ui->toVertexCombo->currentIndex();

    ShortestPathType algorithm =
        static_cast<ShortestPathType>(
            ui->algorithmValueCombo->currentIndex()
        );

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
    ShortestPathType algorithm,
    int start,
    int finish)
{
    ShortestPathResult result;

    switch(algorithm)
    {

        case(ShortestPathType::Dijkstra):
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

        case(ShortestPathType::Floyd):
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

    ui->routingAlgorithmCombo->addItem(
        "Случайная маршрутизация"
        );
    ui->routingAlgorithmCombo->addItem(
        "Лавинная маршрутизация"
        );
    // ui->routingAlgorithmCombo->addItem(
    //     "Маршрутизация по предыдущему опыту"
    //     );
}

void MainWindow::findShortestPaths()
{
    Graph graph = ui->graphWidget->getGraph();

    QElapsedTimer timer;

    timer.start();

    FloydMatrixResult floydResult =
        Floyd::findShortestPaths(graph);

    qint64 floydTime = timer.nsecsElapsed();

    if (floydResult.negativeCycle)
    {
        showNegativeCycle();
        return;
    }

    QVector<PathTableRow> floydRows =
        PathMapper::map(floydResult);

    ui->floydPathWidget->setPaths(floydRows);

    timer.start();

    QVector<QVector<DijkstraResult>> dijkstraResult =
        Dijkstra::findShortestPaths(graph);

    qint64 dijkstraTime = timer.nsecsElapsed();

    QVector<PathTableRow> dijkstraRows =
        PathMapper::map(dijkstraResult);

    ui->dijkstraPathWidget->setPaths(dijkstraRows);

    showExecutionTime(dijkstraTime, floydTime);
}

void MainWindow::showNegativeCycle()
{
    ui->floydPathWidget->clearContents();
    ui->floydPathWidget->setRowCount(0);

    QMessageBox::warning(
        this,
        "Отрицательный цикл",
        "В графе обнаружен отрицательный цикл.\n"
        "Кратчайшие пути не определены."
    );
}

void MainWindow::showExecutionTime(
    qint64 dijkstraTime,
    qint64 floydTime)
{
    double floydMs = floydTime / 1'000'000.0;
    double dijkstraMs = dijkstraTime / 1'000'000.0;

    ui->floydTimeValueLabel->setText(
        QString::number(floydMs, 'f', 3) + " мс"
        );

    ui->dijkstraTimeValueLabel->setText(
        QString::number(dijkstraMs, 'f', 3) + " мс"
        );
}

void MainWindow::saveGraph()
{
    QString fileName =
        QFileDialog::getSaveFileName(
        this,
        "Сохранить граф",
        "",
        "JSON files (*.json)"
    );

    if (fileName.isEmpty())
    {
        return;
    }

    if (!GraphFile::save(
            fileName,
            ui->graphWidget->getGraph()
            )
        )
    {
        QMessageBox::warning(
            this,
            "Ошибка!",
            "Не удалось сохранить граф"
            );
    }
}

void MainWindow::loadGraph()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Загрузить граф",
            "",
            "JSON files (*.json)"
        );

    if (fileName.isEmpty())
    {
        return;
    }

    QVector<Vertex> vertices;
    QVector<QVector<int>> matrix;

    if (!GraphFile::load(
            fileName,
            vertices,
            matrix
            )
        )
    {
        QMessageBox::warning(
            this,
            "Ошибка!",
            "Не удалось загрузить граф"
            );

        return;
    }

    ui->graphWidget->setGraphData(
        vertices,
        matrix
        );
}

void MainWindow::setRoutingAlgorithm()
{
    RoutingType type =
        static_cast<RoutingType>(
            ui->routingAlgorithmCombo->currentIndex()
        );

    RoutingAlgorithm *algorithm =
        algorithmProvider.getAlgorithm(type);

    if (algorithm == nullptr)
    {
        return;
    }

    packetRouter.setRoutingAlgorithm(algorithm);
}

void MainWindow::routePacket()
{
    Graph graph = ui->graphWidget->getGraph();

    if (graph.getVertices().isEmpty())
    {
        return;
    }

    int source = ui->fromRoutingCombo->currentIndex();
    int destination = ui->toRoutingCombo->currentIndex();

    Packet packet;

    packet.id = 0;
    packet.source = source;
    packet.destination = destination;
    packet.currentVertex = source;
    packet.previousVertex = -1;
    packet.ttl = graph.getVertices().size();
    packet.transmissionType =
        ui->datagramRadio->isChecked()
        ? TransmissionType::Datagram
        : TransmissionType::VirtualCircuit;

    packet.route.append(source);

    RoutingResult result =
        packetRouter.routePacket(graph, packet);

    QVector<Packet> animatePackets = result.deliveredPackets;
    animatePackets += result.expiredPackets;

    for (const Packet &packet : animatePackets)
    {
        ui->graphWidget->animatePacket(packet);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
