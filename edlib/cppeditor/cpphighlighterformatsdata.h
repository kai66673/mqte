#pragma once

#include "highlighterformatsmanager.h"

namespace CppEditor {

class CppHighlighterFormatData: public HighlighterFormatData
{
public:
    CppHighlighterFormatData();

    virtual QString languageId() const;
};

}   // namespace CppEditor
