%{


%}

%x COMENTARIO

%%

"|" {return yytext[0];}
";" {return yytext[0];}
"{" {return yytext[0];}
"}" {return yytext[0];}
":" {return yytext[0];}
"," { return yytext[0];}
"/" { return yytext[0];}
"<" { return yytext[0];}
">" { return yytext[0];}


[A-Za-z]+ { yylval.c = strdup(yytext); return string; }
[0-9]+(.[0-9]+)? { yylval.n = atof(yytext); return num; }
([A-Za-z0-9/:\-?=]+\.)+[A-Za-z0-9/:\-?=]+ { yylval.c = strdup(yytext); return url; }

.|\n {}


%%

int yywrap(){
	return 1;
}

