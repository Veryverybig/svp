%{
#include "Node.h"
#include "svp_lexer.h"

void yyerror(const char *msg) {
    printf("%s\n", msg);
}

static svp::Node *root;

%}

%require "3.7"

%verbose
%define parse.error detailed
%define parse.lac full
%define parse.trace

%union {
    int i;
    typename std::string *s;
    typename svp::Node *n;
    typename svp::NodeList *nl;
    typename svp::NodeAttr *na;
    typename svp::NodeAttrList *nal;
}

%token      TK_KW_TX             "tx"
%token      TK_KW_RX             "rx"
%token      TK_KW_LOGIC          "logic"
%token      TK_KW_INTERFACE      "interface"
%token      TK_KW_ENDINTERFACE   "endinterface"
%token<s>   TK_ID
%token<i>   TK_NUM


%type<nl> interface_list
%type<n>  interface
%type<nl> field_list
%type<n>  field
%type<i>  range
%type<i>  range_opt
%type<s>  direction
%type<s>  direction_opt

%start unit

%destructor { delete $$; } <s> <n> <nl>

%printer { YYFPRINTF(yyo, "%s", $$->c_str()); } <s>
%printer { YYFPRINTF(yyo, "%s", $$->toString().c_str()); } <n>
%printer { YYFPRINTF(yyo, "%s", "nodelist"); } <nl>

%%

unit
    : interface_list
        {
            root = new svp::Node("root", svp::NodeKind::ROOT);
            root->children = *$1;
            delete $1;
        }
    ;

interface_list
    : interface
        {
            $$ = new svp::NodeList();
            $$->push_back(*$1);
        }
    | interface_list interface
        {
            $$ = $1;
            $$->push_back(*$2);
            delete $2;
        }
    ;

interface
    : "interface" TK_ID ';' field_list "endinterface"
        {
            $$ = new svp::Node(*$2, svp::NodeKind::INTERFACE);
            $$->children = *$4;
            delete $2;
            delete $4;
        }
    | error
        {
            YYABORT;
        }
    ;

field_list
    : field
        {
            $$ = new svp::NodeList();
            $$->push_back(*$1);
        }
    | field_list field
        {
            $$ = $1;
            $$->push_back(*$2);
            delete $2;
        }
    ;

field
    : direction_opt "logic" range_opt TK_ID range_opt ';'
        {
            $$ = new svp::Node(*$4, svp::NodeKind::FIELD);
            $$->attrs.emplace("direction", *$1);
            $$->attrs.emplace("packed", $3);
            $$->attrs.emplace("unpacked", $5);
            delete $1;
            delete $4;
        }
    ;

range_opt
    : %empty { $$ = 1; }
    | range
    ;

range
    : '[' TK_NUM ']' { $$ = $2; }
    | '[' TK_NUM ':' TK_NUM ']' { $$ = $2 - $4 + 1; }
    ;

direction_opt
    : %empty { $$ = new std::string("tx"); }
    | direction
    ;

direction
    : TK_KW_TX { $$ = new std::string("tx"); }
    | TK_KW_RX { $$ = new std::string("rx"); }
    ;

%%

#include <iostream>
#include "NodeVisitor.h"
int main(int argc, char **argv) {
    if(argc > 1 && !strcmp(argv[1], "-debug"))
        yydebug = 1;
    FILE *fh = fopen("./test_file.sv", "r");
    if(!fh) {
        std::cout << "fail to open file\n";
        return -1;
    }
        

    yyin = fh;

    if(yyparse()) {
        std::cout << "something wrong\n";
        return -1;
    }

    fclose(fh);

    std::cout << *root;

    svp::GenModuleVisitor m("demo");
    m.visit(*root);

    svp::GenInterfaceVisitor i;
    i.visit(*root);

    return 0;
}