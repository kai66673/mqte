#include "mainwindow.h"

#include "edlib.h"
#include "cppeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_editor = EditorsManager::createCppEditor(this);
    setCentralWidget(m_editor);
}
