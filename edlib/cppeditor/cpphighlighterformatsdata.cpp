#include "cpphighlighterformatsdata.h"

namespace CppEditor {

CppHighlighterFormatData::CppHighlighterFormatData()
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

    m_formats.append( new HighlighterFormat( QObject::tr("Builtin Type"),
                                             true,
                                             false,
                                             QColor(224,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Keyword"),
                                             true,
                                             false,
                                             QColor(  0,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Operator"),
                                             false,
                                             false,
                                             QColor(  0,  64,  64),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Preprocessor"),
                                             false,
                                             false,
                                             QColor(  0, 128,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Label"),
                                             false,
                                             false,
                                             QColor( 32,  32,  32),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Comment"),
                                             false,
                                             false,
                                             QColor(224,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Doxygen Comment"),
                                             false,
                                             false,
                                             QColor(165,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Doxygen Tag"),
                                             true,
                                             false,
                                             QColor(165,   0,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Whitespace"),
                                             true,
                                             false,
                                             QColor(224,  96,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("SQL-Embedded Keyword"),
                                             true,
                                             false,
                                             QColor(  0,   0, 165),
                                             QColor() ) );

    // Semantic formats
    m_formats.append( new HighlighterFormat( QObject::tr("Occurrences"),
                                             true,
                                             false,
                                             QColor(),
                                             QColor(222, 222, 222) ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Unused Occurrences"),
                                             true,
                                             false,
                                             QColor(),
                                             QColor(127, 127, 127) ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Type"),
                                             true,
                                             false,
                                             QColor(  0, 255,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Local"),
                                             false,
                                             false,
                                             QColor(127, 127, 127),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Field"),
                                             false,
                                             false,
                                             QColor(255,  64,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Static"),
                                             false,
                                             false,
                                             QColor(  0,  64, 255),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Virtual Method"),
                                             true,
                                             true,
                                             QColor(  0, 255,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("Function"),
                                             true,
                                             false,
                                             QColor(  0, 255,   0),
                                             QColor() ) );

    m_formats.append( new HighlighterFormat( QObject::tr("SQL Table Alias"),
                                             true,
                                             false,
                                             QColor(  0,  96,  96),
                                             QColor() ) );
}

QString CppHighlighterFormatData::languageId() const
{
    return QObject::tr("Cpp");
}

}
