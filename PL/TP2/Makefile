tp2PL: tp2.l
	flex tp2.l
	cc -o tp2PL lex.yy.c

install: tp2
	cp tp2 /usr/local/bin

clean:
		rm -rf lex.yy.c
