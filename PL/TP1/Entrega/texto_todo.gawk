BEGIN{ texto = ""; carater = ""; }

$1==1 { carater = ""; texto = texto "\n"}

$2 !~ /[.,!?\:;]/ { texto = texto  carater $2; 
	if(carater==""){
		carater = " ";
	}
}

$2 ~ /[.,!?\:;]/ { texto = texto $2;}


ENDFILE {	
	nomeFicheiro = "texto_" FILENAME;
	print texto > nomeFicheiro;
	texto = "";
} 

END { print (ARGC-1) " ficheiros processados!"; }
