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

    Graph/vertex.h
    Graph/edge.h
    Graph/graph.h
    Graph/graph.cpp

    Widgets/GraphWidget/graphWidget.h
    Widgets/GraphWidget/graphWidget.cpp
    Widgets/GraphWidget/vertexItem.h
    Widgets/GraphWidget/vertexItem.cpp
    Widgets/GraphWidget/edgeItem.h
    Widgets/GraphWidget/edgeItem.cpp

    Widgets/MatrixWidget/matrixWidget.h
    Widgets/MatrixWidget/matrixWidget.cpp

    Widgets/PathWidget/pathWidget.h
    Widgets/PathWidget/pathWidget.cpp
    Widgets/PathWidget/pathMapper.h
    Widgets/PathWidget/pathMapper.cpp


    Algorithms/algorithm.h
    Algorithms/dijkstra.h
    Algorithms/dijkstra.cpp
    Algorithms/floyd.h
    Algorithms/floyd.cpp
)

target_include_directories(AlgorithmModel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Graph
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/GraphWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/MatrixWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/PathWidget
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms


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
