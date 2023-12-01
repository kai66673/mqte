#include "mainwindow.h"

#include "edlib.h"
#include "goeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_editor = EditorsManager::createGoEditor(this);
    setCentralWidget(m_editor);
}
