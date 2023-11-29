#include "edlib.h"
#include "highlighterformatsmanager.h"
#include "pythonhighlighterformatsdata.h"
#include "cpphighlighterformatsdata.h"
#include "pythoneditorwidget.h"
#include "cppeditor.h"

#include <cpptoolssettings.h>
#include <texteditorsettings.h>

EditorsManager* EditorsManager::m_instance = nullptr;

EditorsManager::EditorsManager()
{
    new TextEditor::TextEditorSettings;
    new CppTools::CppToolsSettings;

    m_highlighterFormatsManager = new HighlighterFormatsManager;
    m_highlighterFormatsManager->registerLanguageHighlighter(new PythonEditor::PythonHighlighterFormatData);
    m_highlighterFormatsManager->registerLanguageHighlighter(new CppEditor::CppHighlighterFormatData);
}

EditorsManager::~EditorsManager()
{
    delete m_highlighterFormatsManager;
}

EditorsManager *EditorsManager::instanse()
{
    return m_instance? m_instance : m_instance = new EditorsManager();
}

////////////////////////////////////////////////////////////////
/// static API

PythonEditor::EditorWidget *EditorsManager::createPythonEditor(QWidget *parent)
{
    instanse();
    PythonEditor::EditorWidget *widget = new PythonEditor::EditorWidget(parent);
    widget->onSettingsChanged();
    return widget;
}

CppEditor::EditorWidget *EditorsManager::createCppEditor(QWidget *parent)
{
    instanse();
    CppEditor::EditorWidget *widget = new CppEditor::EditorWidget(parent);
    widget->onSettingsChanged();
    return widget;
}
