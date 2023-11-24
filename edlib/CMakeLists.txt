cmake_minimum_required(VERSION 3.5)

project(edlib VERSION 0.1 LANGUAGES CXX)

set (TEXTEDITOR_HEADERS
    texteditor/texteditor_global.h
    texteditor/basetexteditor.h
    texteditor/texteditor.h
    texteditor/texteditoroverlay.h
    texteditor/refactoroverlay.h
    texteditor/basetextdocument.h
    texteditor/basetexteditor_p.h
    texteditor/texteditorsettings.h
    texteditor/behaviorsettings.h
    texteditor/displaysettings.h
    texteditor/fontsettings.h
    texteditor/completionsettings.h
    texteditor/typingsettings.h
    texteditor/storagesettings.h
    texteditor/extraencodingsettings.h
    texteditor/icodestylepreferences.h
    texteditor/icodestylepreferencesfactory.h
    texteditor/colorscheme.h
    texteditor/basetextdocumentlayout.h
    texteditor/texteditorconstants.h
    texteditor/indenter.h
    texteditor/tabsettings.h
    texteditor/syntaxhighlighter.h
    texteditor/highlighterformatsmanager.h
#    texteditor/highlighterformatsconfigurewidget.h
    texteditor/codestylepool.h
    texteditor/codecselector.h
    texteditor/convenience.h
    texteditor/autocompleter.h

    texteditor/core/corelib_global.h
    texteditor/core/coreconstants.h
    texteditor/core/itexteditor.h
    texteditor/core/ifile.h
    texteditor/core/textfile.h
    texteditor/core/infobar.h
    texteditor/core/ifindsupport.h
    texteditor/core/manhattanstyle.h
    texteditor/core/styleanimator.h

    texteditor/codeassist/codeassistant.h
    texteditor/codeassist/runner.h
    texteditor/codeassist/iassistinterface.h
    texteditor/codeassist/iassistprovider.h
    texteditor/codeassist/completionassistprovider.h
    texteditor/codeassist/defaultassistinterface.h

    texteditor/snippets/isnippetprovider.h
    texteditor/snippets/plaintextsnippetprovider.h
    texteditor/snippets/reuse.h
    texteditor/snippets/snippet.h
    texteditor/snippets/snippeteditor.h
    texteditor/snippets/snippetscollection.h
    texteditor/snippets/snippetssettings.h

    texteditor/tooltip/tooltip.h
    texteditor/tooltip/tipcontents.h
    texteditor/tooltip/tipfactory.h
    texteditor/tooltip/tips.h

    texteditor/utils/utils_global.h
    texteditor/utils/settingsutils.h
    texteditor/utils/qtcfileutils.h
    texteditor/utils/qtcassert.h
    texteditor/utils/savefile.h
    texteditor/utils/algorithm.h
    texteditor/utils/hostosinfo.h
    texteditor/utils/osspecificaspects.h
    texteditor/utils/consoleprocess.h
    texteditor/utils/consoleprocess_p.h
    texteditor/utils/qtcprocess.h
    texteditor/utils/environment.h
    texteditor/utils/unixutils.h
    texteditor/utils/stringutils.h
    texteditor/utils/uncommentselection.h
    texteditor/utils/persistentsettings.h
    texteditor/utils/textfileformat.h
    texteditor/utils/changeset.h
    texteditor/utils/stylehelper.h
)

set (TEXTEDITOR_SOURCES
    texteditor/texteditor.cpp
    texteditor/texteditoroverlay.cpp
    texteditor/refactoroverlay.cpp
    texteditor/texteditorsettings.cpp
    texteditor/behaviorsettings.cpp
    texteditor/displaysettings.cpp
    texteditor/fontsettings.cpp
    texteditor/completionsettings.cpp
    texteditor/typingsettings.cpp
    texteditor/storagesettings.cpp
    texteditor/extraencodingsettings.cpp
    texteditor/icodestylepreferences.cpp
    texteditor/icodestylepreferencesfactory.cpp
    texteditor/colorscheme.cpp
    texteditor/basetextdocumentlayout.cpp
    texteditor/basetextdocument.cpp
    texteditor/indenter.cpp
    texteditor/tabsettings.cpp
    texteditor/syntaxhighlighter.cpp
    texteditor/highlighterformatsmanager.cpp
#    texteditor/highlighterformatsconfigurewidget.cpp
    texteditor/codestylepool.cpp
    texteditor/codecselector.cpp
    texteditor/convenience.cpp
    texteditor/autocompleter.cpp

    texteditor/core/itexteditor.cpp
    texteditor/core/ifile.cpp
    texteditor/core/textfile.cpp
    texteditor/core/infobar.cpp
    texteditor/core/ifindsupport.cpp
    texteditor/core/manhattanstyle.cpp
    texteditor/core/styleanimator.cpp

    texteditor/codeassist/codeassistant.cpp
    texteditor/codeassist/runner.cpp
    texteditor/codeassist/iassistinterface.cpp
    texteditor/codeassist/iassistprovider.cpp
    texteditor/codeassist/completionassistprovider.cpp
    texteditor/codeassist/defaultassistinterface.cpp

    texteditor/snippets/isnippetprovider.cpp
    texteditor/snippets/plaintextsnippetprovider.cpp
    texteditor/snippets/snippet.cpp
    texteditor/snippets/snippeteditor.cpp
    texteditor/snippets/snippetscollection.cpp
    texteditor/snippets/snippetssettings.cpp

    texteditor/tooltip/tooltip.cpp
    texteditor/tooltip/tipcontents.cpp
    texteditor/tooltip/tipfactory.cpp
    texteditor/tooltip/tips.cpp

    texteditor/utils/qtcfileutils.cpp
    texteditor/utils/qtcassert.cpp
    texteditor/utils/savefile.cpp
    texteditor/utils/hostosinfo.cpp
    texteditor/utils/consoleprocess.cpp
    texteditor/utils/consoleprocess_unix.cpp
    texteditor/utils/qtcprocess.cpp
    texteditor/utils/environment.cpp
    texteditor/utils/unixutils.cpp
    texteditor/utils/stringutils.cpp
    texteditor/utils/uncommentselection.cpp
    texteditor/utils/persistentsettings.cpp
    texteditor/utils/textfileformat.cpp
    texteditor/utils/changeset.cpp
    texteditor/utils/stylehelper.cpp
)

set (PYTHONEDITOR_HEADERS
    pythoneditor/tools/lexical/pythonscanner.h
    pythoneditor/tools/lexical/pythonformattoken.h
    pythoneditor/tools/lexical/sourcecodestream.h
    pythoneditor/tools/pythonhighlighter.h
    pythoneditor/tools/pythonindenter.h
    pythoneditor/pythoneditor_global.h
    pythoneditor/pythoneditorwidget.h
    pythoneditor/pythonhighlighterformatsdata.h
)

set (PYTHONEDITOR_SOURCES
    pythoneditor/tools/lexical/pythonscanner.cpp
    pythoneditor/tools/pythonindenter.cpp
    pythoneditor/tools/pythonhighlighter.cpp
    pythoneditor/pythoneditorwidget.cpp
    pythoneditor/pythonhighlighterformatsdata.cpp
)

set (EDLIB_HEADERS
    edlib_global.h
    edlib.h
)

set (EDLIB_SOURCES
    edlib.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${TEXTEDITOR_SOURCES}
    ${TEXTEDITOR_HEADERS}
    ${PYTHONEDITOR_SOURCES}
    ${PYTHONEDITOR_HEADERS}
    ${EDLIB_SOURCES}
    ${EDLIB_HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_compile_definitions(${PROJECT_NAME} PRIVATE EDLIB_LIBRARY)
target_compile_definitions(${PROJECT_NAME} PRIVATE TEXTEDITOR_LIBRARY)
target_compile_definitions(${PROJECT_NAME} PRIVATE QTCREATOR_UTILS_LIB)
target_compile_definitions(${PROJECT_NAME} PRIVATE CORELIB_LIBRARY)
target_compile_definitions(${PROJECT_NAME} PRIVATE PYTHONEDITOR_LIBRARY)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor/core)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor/utils)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor/tooltip)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor/snippets)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/texteditor/codeassist)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pythoneditor)
