function ordena(i1, v1, i2, v2){
    i1 = i1 ""
    i2 = i2 ""
    if (i1 < i2)
        return -1
    return (i1 != i2)
}
BEGIN{ }

$5 ~ /^R/ {

		adverbios[$3]++;
	}

$5 ~ /^V/ {

		verbos[$3]++;
	}

$5 ~ /^A/ {

		adjetivos[$3]++;
	}

$5 ~ /^N/ {

		nomes[$3]++;
	}	

END {
	PROCINFO["sorted_in"] = "ordena";

	titl[1] = "Adverbios";
	titl[2] = "Verbos";
	titl[3] = "Adjetivos";
	titl[4] = "Nomes";
	fics[1] = "adverbios.html";
	fics[2] = "verbos.html";
	fics[3] = "adjetivos.html";
	fics[4] = "nomes.html";
	imprimeFicheiro(adverbios,fics[1],titl[1]);
	imprimeFicheiro(verbos,fics[2],titl[2]);
	imprimeFicheiro(adjetivos,fics[3],titl[3]);
	imprimeFicheiro(nomes,fics[4],titl[4]);

	telaPrincipalHtml(titl,fics,"principal_pergunta3.html");
	
} 

function imprimeFicheiro(a,f,titulo){


	print "<html><head>\n<title>Lista de Palavras - " titulo "</title>\n</head>" > f;
	
	print "<body>\n<h1>Lista de Palavras</h1>\n<dl>" >> f;
	
	print "<h2> " titulo " </h2>\n<p> </p>\n<head>\n<style>table, th, td {   border: 1px solid black; }</style>\n</head>\n<table style=\"width:60%\">\n\t<tr>\n\t\t<th>Palavra</th>\n\t\t<th>Número de ocorrências</th>\n\t</tr>" >> f;	

	for(x in a){
		texto = "\t<tr>\n\t\t<td> " x " </td>\n\t\t<td> " a[x] " </td>\n\t</tr>";
			print texto >> f;

	}
	
	print "</table>" >> f;
}


function telaPrincipalHtml(titulos,ficheiros,nomFic){

texto="<html>\n";
texto = texto "<head>\n"
texto = texto "<meta charset=’UTF-8’/>\n"
texto = texto "<style>table, th, td {border: 1px solid black;\n"
texto = texto "border-collapse: collapse;} th, td {padding: 5px;} th\n"
texto = texto "{text-align: left;} </style>\n"
texto = texto "</head>\n"
texto = texto "<body>\n"
texto = texto "<h1 align="center"> Classes de Palavras </h1>\n"
texto = texto "<hr>\n"

for(x in titulos){

	texto = texto "<li><a href=" ficheiros[x] "> " titulos[x] " </a></li>\n"

}
texto = texto "</body>\n"
texto = texto "</html>\n"

print texto > nomFic;

}
