// Copyright (c) 2008 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef CPLUSPLUS_LEXER_H
#define CPLUSPLUS_LEXER_H

#include "cppeditor_global.h"
#include "Token.h"


namespace CPlusPlus {

class CPLUSPLUS_EXPORT Lexer
{
    Lexer(const Lexer &other);
    void operator =(const Lexer &other);

public:
    enum State {
        State_Default,
        State_MultiLineComment,
        State_MultiLineDoxyComment
    };

    enum SqlState {
        SqlState_StartDeclaration,      // In Start Declaration - want T_SQL_EXEC, sql mode disabled
        SqlState_Exec,                  // Previous Word (skip commentd) is T_SQL_EXEC - want T_SQL_SQL, sql mode disabled
        SqlState_ExecSql,               // Previous Two Words are T_SQL_EXEC and T_SQL_SQL - sql mode enabled until T_SEMICOLON
        SqlState_Invalid                // In this State EXEC SQL disabled until T_SEMICOLON or T_LBRACE or T_RBRACE
    };

    Lexer(const char *firstChar, const char *lastChar);
    ~Lexer();


    bool qtMocRunEnabled() const;
    void setQtMocRunEnabled(bool onoff);

    bool cxx0xEnabled() const;
    void setCxxOxEnabled(bool onoff);

    bool objCEnabled() const;
    void setObjCEnabled(bool onoff);

    bool singleLineCommentEnabled() const;
    void setSingleLineCommentEnabled( bool onoff );

    bool extraExecSqlEnabled() const;
    void setExtraExecSqlEnabled( bool onoff );

    void scan(Token *tok);

    inline void operator()(Token *tok)
    { scan(tok); }

    unsigned tokenOffset() const;
    unsigned tokenLength() const;
    const char *tokenBegin() const;
    const char *tokenEnd() const;
    unsigned currentLine() const;

    bool scanCommentTokens() const;
    void setScanCommentTokens(bool onoff);

    bool scanKeywords() const;
    void setScanKeywords(bool onoff);

    bool scanAngleStringLiteralTokens() const;
    void setScanAngleStringLiteralTokens(bool onoff);

    void setStartWithNewline(bool enabled);

    int state() const;
    void setState(int state);

    int sqlState() const;
    void setSqlState( int sqlState );

    bool isIncremental() const;
    void setIncremental(bool isIncremental);

private:
    void scan_helper(Token *tok);
    void setSource(const char *firstChar, const char *lastChar);
    static int classify(const char *string, int length, bool q, bool cxx0x, bool sc, int scState = SqlState_Invalid );
    static int classifyObjCAtKeyword(const char *s, int n);
    static int classifyOperator(const char *string, int length);

    void pushLineStartOffset();

    inline void yyinp()
    {
        if (++_currentChar == _lastChar)
            _yychar = 0;
        else {
            _yychar = *_currentChar;
            if (_yychar == '\n')
                pushLineStartOffset();
        }
    }

    inline unsigned char nextChar()
    {
        if ( _currentChar + 1 == _lastChar )
            return 0;
        return *(_currentChar + 1);
    }

private:
    struct Flags {
        unsigned _isIncremental: 1;
        unsigned _scanCommentTokens: 1;
        unsigned _scanKeywords: 1;
        unsigned _scanAngleStringLiteralTokens: 1;
        unsigned _qtMocRunEnabled: 1;
        unsigned _cxx0xEnabled: 1;
        unsigned _objCEnabled: 1;
        unsigned _isSingleLineCommentEnabled: 1;
        unsigned _isExtraExecSqlEnabled: 1;
    };

    const char *_firstChar;
    const char *_currentChar;
    const char *_lastChar;
    const char *_tokenStart;
    unsigned char _yychar;
    int _state;
    int _sqlState;
    union {
        unsigned _flags;
        Flags f;
    };
    unsigned _currentLine;
};

} // namespace CPlusPlus


#endif // CPLUSPLUS_LEXER_H
