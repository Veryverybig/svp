comp: l p

FLEX_OPTS := 					\
	--noline 					\
	--yylineno 					\
	--header-file=svp_lexer.h 	\
	--outfile=svp_lexer.cpp

l:
	flex $(FLEX_OPTS) svp.l


BISON_OPTS :=					\
	--no-lines 					\
	--defines=svp_parser.h 		\
	--output=svp_parser.cpp

p:
	bison $(BISON_OPTS) svp.y