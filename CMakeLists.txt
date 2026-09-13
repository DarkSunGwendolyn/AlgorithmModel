cmake_minimum_required(VERSION 3.19)
project(AlgorithmModel LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()


qt_add_executable(AlgorithmModel
    WIN32 MACOSX_BUNDLE
    main.cpp

    mainwindow.h
    mainwindow.cpp
    mainwindow.ui

    Models/Graph/vertex.h
    Models/Graph/edge.h
    Models/Graph/graph.h
    Models/Graph/graph.cpp

    Models/Packet/packetFactory.h
    Models/Packet/packetFactory.cpp
    Models/Packet/packet.h

    Models/Routing/routingTable.h

    Algorithms/Routing/experienceRouting.h
    Algorithms/Routing/experienceRouting.cpp

    Widgets/GraphWidget/graphWidget.h
    Widgets/GraphWidget/graphWidget.cpp
    Widgets/GraphWidget/vertexItem.h
    Widgets/GraphWidget/vertexItem.cpp
    Widgets/GraphWidget/edgeItem.h
    Widgets/GraphWidget/edgeItem.cpp
    Widgets/GraphWidget/packetStatus.h
    Widgets/GraphWidget/packetItem.h
    Widgets/GraphWidget/packetItem.cpp

    Widgets/MatrixWidget/matrixWidget.h
    Widgets/MatrixWidget/matrixWidget.cpp

    Widgets/PathWidget/pathWidget.h
    Widgets/PathWidget/pathWidget.cpp
    Widgets/PathWidget/pathMapper.h
    Widgets/PathWidget/pathMapper.cpp
    Widgets/PathWidget/pathTableRow.h

    Widgets/PacketTableWidget/packetMapper.h
    Widgets/PacketTableWidget/packetMapper.cpp
    Widgets/PacketTableWidget/packetTableWidget.h
    Widgets/PacketTableWidget/packetTableWidget.cpp
    Widgets/PacketTableWidget/packetTableRow.h

    Widgets/RoutingTableWidget/routingTableWidget.h
    Widgets/RoutingTableWidget/routingTableWidget.cpp


    Algorithms/ShortestPath/shortestPathType.h
    Algorithms//ShortestPath/dijkstra.h
    Algorithms//ShortestPath/dijkstra.cpp
    Algorithms//ShortestPath/floyd.h
    Algorithms//ShortestPath/floyd.cpp

    Algorithms/Routing/routingAlgorithm.h
    Algorithms/Routing/randomRouting.h
    Algorithms/Routing/randomRouting.cpp
    Algorithms/Routing/floodingRouting.h
    Algorithms/Routing/floodingRouting.cpp
    Algorithms/Routing/routingType.h
    Algorithms/Routing/routingAlgorithmProvider.h
    Algorithms/Routing/routingAlgorithmProvider.cpp

    Routing/routingResult.h
    Routing//packetRouter.h
    Routing/packetRouter.cpp
    Routing/transmissionType.h
    Routing/transmissionMethod.h
    Routing/transmissionMethod.cpp
    Routing/datagram.h
    Routing/datagram.cpp
    Routing/virtualCircuit.h
    Routing/virtualCircuit.cpp

    File/graphFile.h
    File/graphFile.cpp
)

target_include_directories(AlgorithmModel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Models
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Graph
        ${CMAKE_CURRENT_SOURCE_DIR}/Models/Packet
         ${CMAKE_CURRENT_SOURCE_DIR}/Models/Routing

        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/GraphWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/MatrixWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/PathWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/PacketTableWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/RoutingTableWidget


        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/ShortestPath
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/Routing

        ${CMAKE_CURRENT_SOURCE_DIR}/Routing

        ${CMAKE_CURRENT_SOURCE_DIR}/File
)

target_link_libraries(AlgorithmModel
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS AlgorithmModel
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET AlgorithmModel
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
