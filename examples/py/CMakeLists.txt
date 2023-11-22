cmake_minimum_required(VERSION 3.5)

project(pyeditor VERSION 0.1 LANGUAGES CXX)

set (PYEDITOR_SOURCES
    mainwindow.cpp
    main.cpp
)

set (PYEDITOR_HEADERS
    mainwindow.h
)

add_executable(${PROJECT_NAME}
    ${PYEDITOR_SOURCES}
    ${PYEDITOR_HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    edlib
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../edlib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../edlib/pythoneditor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../edlib/texteditor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../edlib/texteditor/core)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../edlib/texteditor/utils)
