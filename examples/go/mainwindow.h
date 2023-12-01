#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace GoEditor {
    class EditorWidget;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);


private:
    GoEditor::EditorWidget *m_editor;
};

#endif // MAINWINDOW_H
