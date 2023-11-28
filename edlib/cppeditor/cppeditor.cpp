#include "cppeditor.h"

namespace CppEditor {

EditorWidget::EditorWidget(QWidget *parent)
    : TextEditor::TextEditorWidget(parent)
{
    m_commentDefinition.setMultiLineStart(QLatin1String("/*"));
    m_commentDefinition.setMultiLineEnd(QLatin1String("*/"));
    m_commentDefinition.setSingleLine(QLatin1String("//"));

    setParenthesesMatchingEnabled(true);
    setMarksVisible(true);
    setCodeFoldingSupported(true);

//    setIndenter(new PythonIndenter());

    m_highlighter = new Internal::CppHighlighter(document());

}

EditorWidget::~EditorWidget()
{ }

void EditorWidget::unCommentSelection()
{
    Utils::unCommentSelection(this, m_commentDefinition);
}

void EditorWidget::onSettingsChanged()
{
    TextEditor::TextEditorWidget::onSettingsChanged();
    m_highlighter->onFormatSettingsChanged();
}

}   // namespace CppEditor
