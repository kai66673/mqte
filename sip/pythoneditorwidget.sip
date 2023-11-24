%Import QtWidgets/QtWidgetsmod.sip

%Include texteditorwidget.sip

%If (Qt_5_0_0 -)

namespace PythonEditor
{

class EditorWidget : public TextEditor::TextEditorWidget
{

    %TypeHeaderCode
    #include "pythoneditorwidget.h"
    %End

public:
    EditorWidget(QWidget *parent = 0);
    virtual ~EditorWidget();

    virtual void unCommentSelection();
    virtual void onSettingsChanged();

};

};

%End
