/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (info@qt.nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef CPPHIGHLIGHTER_H
#define CPPHIGHLIGHTER_H

#include "cppeditor_global.h"

#include "cppeditorenums.h"
#include <syntaxhighlighter.h>
#include <QtGui/QTextCharFormat>
#include <QtCore/QtAlgorithms>

namespace CppEditor {

namespace Internal {

class CppHighlighter : public TextEditor::SyntaxHighlighter
{
    Q_OBJECT

public:
    CppHighlighter(QTextDocument *document = 0);

    virtual void highlightBlock(const QString &text);

    bool singleLineCommentEnabled() const { return m_singleLineCommentEnabled; }
    void setSingleLineCommentEnabled( bool onoff ) { m_singleLineCommentEnabled = onoff; }
    bool extraExecSqlEnabled() const { return m_extraExecSqlEnabled; }
    void setExtraExecSqlEnabled( bool onoff ) { m_extraExecSqlEnabled = onoff; }

    void onFormatSettingsChanged( bool forceRehilight = true );

    QTextCharFormat labelFormat() const { return m_formats[CppLabelFormat]; }

private:
    void highlightWord(QStringRef word, int position, int length);
    void highlightLine(const QString &line, int position, int length,
                       const QTextCharFormat &format);

    void highlightDoxygenComment(const QString &text, int position,
                                 int length);

    bool isPPKeyword(const QStringRef &text) const;
    bool isQtKeyword(const QStringRef &text) const;

    bool m_singleLineCommentEnabled;
    bool m_extraExecSqlEnabled;

    QTextCharFormat m_formats[NumCppFormats];
};

} // namespace Internal
} // namespace CppEditor

#endif // CPPHIGHLIGHTER_H
