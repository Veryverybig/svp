%{

#include "Node.h"
#include "svp_parser.h"

%}

WS      [ \t\n]
ID      [_a-zA-Z][_a-zA-Z0-9]*
NUM     0|[1-9][0-9]*

%option noyywrap

%x LCOMMENT
%x BCOMMENT

%%

{NUM}           { yylval.i = atoi(yytext); return TK_NUM; }

"//"            { BEGIN(LCOMMENT); }
"/*"            { BEGIN(BCOMMENT); }

"logic"         { return TK_KW_LOGIC; }
"interface"     { return TK_KW_INTERFACE; }
"endinterface"  { return TK_KW_ENDINTERFACE; }
"tx"            { return TK_KW_TX; }
"rx"            { return TK_KW_RX; }
{ID}            { yylval.s = new std::string(yytext); return TK_ID; }
{WS}            {}

.               { return yytext[0]; }

<LCOMMENT>"\n"  { BEGIN(INITIAL); }
<LCOMMENT>.     {}
<BCOMMENT>"*/"  { BEGIN(INITIAL); }
<BCOMMENT>.     {}


%%