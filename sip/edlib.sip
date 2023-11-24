%Module edlib

%Import QtWidgets/QtWidgetsmod.sip

%Include pythoneditorwidget.sip

class EditorsManager
{

    %TypeHeaderCode
    #include "../edlib/edlib.h"
    %End

public:
    static PythonEditor::EditorWidget *createPythonEditor(QWidget *parent = nullptr);
};
