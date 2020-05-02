# Os ficheiros código necessários para gerar
OBJECTS = y.tab.c
# O executável                 
EXEC = tp3PL                                                 
# Flags                                   
FLAGS = -g -lm -I/usr/include/mysql/ -lmysqlclient                                                       
# Compilador                          
CC = gcc  

FF = flex

YY = yacc

OBJF = tp3.l                                                            

OBJY = tp3.y
# Ações 

target:

	$(FF) $(OBJF)

	$(YY) $(OBJY)

	$(CC) $(OBJECTS) -o $(EXEC) $(FLAGS) 

	mv $(EXEC) /usr/local/bin/



clean:
		rm -rf lex.yy.c y.tab.*
