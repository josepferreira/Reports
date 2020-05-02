

BEGIN{IGNORECASE=1;}

					{x = split($6, p, "[=|]");
						pos = "";
						for(i=2; i<x; i+=2)
							pos = pos " " p[i];
						a[$3][pos][$2];	
					}

END{
	asorti(a, aux)

	imprimeFicheiro(a, aux, "dicionario.html", "Dicionário");

}


function imprimeFicheiro(a, d, filename,titulo){


	print "<html><head>\n<title> " titulo "</title>\n</head>" > filename;
	
	print "<body>\n<h1>Lista de Palavras</h1>\n<dl>" >> filename;

		print "<ul>" >> filename;
	for(x in d){
		print "<li>" "lema: " d[x] " {" >> filename; 
		print "<ul style=\"list-style-type:circle\">" >> filename;
		for(y in a[d[x]]){
			for(z in a[d[x]][y]){
				print "<li>" "pos: " y " -> palavra: " z " </li>" >> filename;
			}
		}
		print "</ul>" >> filename;
	print "}</li>" >> filename;
	}

	print "</body>" >> filename;
	print "</html>" >> filename;


}