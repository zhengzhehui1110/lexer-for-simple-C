# lexer-for-simple-C
a lexer for simple C in language C
简易C语言词法分析器
code rule:
identification for variable	1	ID
const int	2	CINT
const real	3	CREAL
const char	4	CCHAR
const string	5	CSTRING
Main	6	MAIN
Void	7	VOID
int	8	INT
Char	9	CHAR
Float	10	FLOAT
Printf	11	PRINTF
Scanf	12	SCANF
Else	13	ELSE
If	14	IF
Return	15	RETURN
while	16	WHILE
string	17	STRING
+	100	ADD
-	101	SUB
*	102	MUL
/	103	DIV
=	104	ASSIGN
>	105	GT
<	106	LT
<=	107	NGT
>=	108	NLT
%	109	MOD
!	110	NOT
&&	111	AND
||	112	OR
==	113	EQUAL
&	114	QUOTE
|	115	DQUOTE
,	150	COMMA
;	151	SEMI
(	152	LBR
)	153	RBR
[	154	LSBR
]	155	RSBR
{	156	LBRACE
}	157	RBRACE
