%Import QtWidgets/QtWidgetsmod.sip

%If (Qt_5_0_0 -)

namespace TextEditor
{

class TextEditorWidget: public QPlainTextEdit
{

    %TypeHeaderCode
    #include "texteditor.h"
    %End

public:
    TextEditorWidget(QWidget *parent);
    ~TextEditorWidget();

};

};

%End
