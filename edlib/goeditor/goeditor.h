#pragma once

#include <QObject>

#include "goeditor_global.h"
#include "gohighlighter.h"

#include <texteditor.h>
#include <uncommentselection.h>

namespace GoEditor {

class GOEDITOR_EXPORT EditorWidget : public TextEditor::TextEditorWidget
{
    Q_OBJECT

public:
    EditorWidget(QWidget *parent = 0);
    virtual ~EditorWidget();

    virtual void unCommentSelection();
    virtual void onSettingsChanged();

private:
    Utils::CommentDefinition m_commentDefinition;
    Internal::GoHighlighter *m_highlighter;
};

}   // namespace GoEditor
