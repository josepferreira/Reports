function ordena(i1, v1, i2, v2){
     # numerical index comparison, ascending order
     return (v2 - v1);
}

BEGIN{ }

$5=="NP" {

		nomes[$2]++;
	}

END {
	
	PROCINFO["sorted_in"] = "ordena"
	for(x in nomes){
		print x " -> " nomes[x] " vezes!"

	}

	imprimeFicheiro(nomes, "personagens.html", "Personagens");

}

function imprimeFicheiro(a,f,titulo){


	print "<html><head>\n<title>" titulo "</title>\n</head>" > f;
	
	
	print "<h2> " titulo " </h2>\n<p> </p>\n<head>\n<style>table, th, td {   border: 1px solid black; }</style>\n</head>\n<table style=\"width:60%\">\n\t<tr>\n\t\t<th>Palavra</th>\n\t\t<th>Número de ocorrências</th>\n\t</tr>" >> f;	

	for(x in a){
		texto = "\t<tr>\n\t\t<td> " x " </td>\n\t\t<td> " a[x] " </td>\n\t</tr>";
			print texto >> f;

	}
	
	print "</table>" >> f;
}
