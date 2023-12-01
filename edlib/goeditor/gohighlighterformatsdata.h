#pragma once

#include "highlighterformatsmanager.h"

namespace GoEditor {

class GoHighlighterFormatData: public HighlighterFormatData
{
public:
    GoHighlighterFormatData();

    virtual QString languageId() const;
};

}   // namespace GoEditor
