#pragma once

#include <QObject>

#include "cppeditor_global.h"
#include "cpphighlighter.h"

#include <texteditor.h>
#include <uncommentselection.h>

namespace CppEditor
{

class CPPEDITOR_EXPORT EditorWidget : public TextEditor::TextEditorWidget
{
    Q_OBJECT

public:
    EditorWidget(QWidget *parent = 0);
    virtual ~EditorWidget();

    virtual void unCommentSelection();
    virtual void onSettingsChanged();

private:
    Utils::CommentDefinition m_commentDefinition;
    Internal::CppHighlighter *m_highlighter;
};

}   // namespace CppEditor
