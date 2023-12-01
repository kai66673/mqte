#include "gohighlighterformatsdata.h"

namespace GoEditor {

GoHighlighterFormatData::GoHighlighterFormatData()
{
    m_formats.append( new HighlighterFormat( QObject::tr("Number"),
                                             false,
                                             false,
                                             QColor(  0,   0, 224),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("String"),
                                             false,
                                             false,
                                             QColor(  0,   0, 128),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Keyword"),
                                             true,
                                             false,
                                             QColor(  0,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Type"),
                                             true,
                                             false,
                                             QColor(224,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Operator"),
                                             false,
                                             false,
                                             QColor(160, 64, 0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Comment"),
                                             false,
                                             false,
                                             QColor(224,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Whitespace"),
                                             true,
                                             false,
                                             QColor(  0,   0, 165),
                                             QColor() ) );
}

QString GoHighlighterFormatData::languageId() const
{
    return QObject::tr("Go");
}

}   // namespace GoEditor
