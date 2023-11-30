#include "goeditor.h"

namespace GoEditor {

EditorWidget::EditorWidget(QWidget *parent)
    : TextEditor::TextEditorWidget(parent)
{
    m_commentDefinition.setMultiLineStart(QLatin1String("/*"));
    m_commentDefinition.setMultiLineEnd(QLatin1String("*/"));
    m_commentDefinition.setSingleLine(QLatin1String("//"));

    setParenthesesMatchingEnabled(true);
    setMarksVisible(true);
    setCodeFoldingSupported(true);
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

}   // namespace GoEditor
