#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace CppEditor {
    class EditorWidget;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);


private:
    CppEditor::EditorWidget *m_editor;
};

#endif // MAINWINDOW_H
