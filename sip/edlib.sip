%Module edlib

%Import QtWidgets/QtWidgetsmod.sip

%Include pythoneditorwidget.sip
%Include cppeditorwidget.sip

class EditorsManager
{

    %TypeHeaderCode
    #include "../edlib/edlib.h"
    %End

public:
    static PythonEditor::EditorWidget *createPythonEditor(QWidget *parent = nullptr);
    static CppEditor::EditorWidget *createCppEditor(QWidget *parent = nullptr);
};
