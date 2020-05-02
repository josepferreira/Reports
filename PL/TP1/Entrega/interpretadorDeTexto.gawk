BEGIN{IGNORECASE=1;primeira="";segunda="";terceira="";}
 
!(/^$/)	{	x = split($6, p, "[=|]");
		terceira = p[2];
		prob[$2][primeira][segunda][terceira]++;
		
		primeira = segunda;
		segunda = terceira;
	}

ENDFILE { primeira = ""; segunda = ""; terceira = ""; }

END {	pasta = "interpretadorDeTexto"
	criaPasta(pasta)

	for(x in prob){
		numPaginas++;
		criaPaginaPalavra(x,prob[x],pasta);
	}

	asorti(prob,destino)
	criaPaginaPrincipal(destino, pasta "/" pasta ".html")
	
	print numPaginas " Páginas Criadas!"
}


function criaPasta(nomePasta){
	if (system(("mkdir " nomePasta)) != 0) 
		print "Não foi possível criar a diretoria de novo!"
}

function criaPaginaPrincipal(a,nomFic){

	texto="<html><head>\n<title>Página Principal - " nomFic "</title>\n</head>\n"

	texto = texto "<head>\n"
	texto = texto "<meta charset=’UTF-8’/>\n"
	texto = texto "<style>table, th, td {border: 1px solid black;\n"
	texto = texto "border-collapse: collapse;} th, td {padding: 5px;} th\n"
	texto = texto "{text-align: left;}\n"

	texto = texto "li {\n"
	texto = texto "\tdisplay: block;\n"
	texto = texto "\twidth: 25%;\n"
	texto = texto "\tfloat: left;\n"
	texto = texto "}\n"
	texto = texto "</style>\n"

	texto = texto "</head>\n"
	texto = texto "<body>\n"
	texto = texto "<h1 align="center"> Palavras </h1>\n"
	texto = texto "<hr>\n"

	for(x in a){
		texto = texto "<li><a href=" a[x] ".html> " a[x] " </a></li>\n"

	}
	texto = texto "</body>\n"
	texto = texto "</html>\n"

	print texto > nomFic;
}


function processaProbabilidade(t){
	total = 0;
	for(q in t){
		total += t[q];
	}
	
	for(q in t){
		t[q] = (t[q] / total) * 100;
	}

}

function criaPaginaPalavra(b,a,nomePasta){
	
	if(b ~ /\//){
		gsub("/","|",b);
		print "ERRO! Não pode aparecer ficheiros com o carater /, substituído por |";
	}	
	
	f = nomePasta "/" b ".html";
	print "<html><head>\n<title>Palavra - " b "</title>\n</head>" > f;

	print "<body>\n<h1>Palavra - " b "</h1>\n<dl>" >> f;
	
	print "<h2> " b " </h2>\n<p> </p>\n<head>\n<style>table, th, td {   border: 1px solid black; }</style>\n</head>\n<table style=\"width:60%\">\n\t<tr>\n\t\t<th>Classe Palavra 2x anterior</th>\n\t\t<th>Classe Palavra anterior</th>\n\t\t<th>Classe Palavra Atual</th>\n\t\t<th>Percentagem</th>\n\t</tr>" >> f;	

	for(y in a){
		for(z in a[y]){
			processaProbabilidade(a[y][z]);
			for(w in a[y][z]){

				texto = "<tr>\n\t<td>" y "</td>\n\t<td>" z "</td>\n\t<td>" w "</td>\n\t<td>" a[y][z][w] "%</td>\n</tr>"
				print texto >> f;
				}
			}
		}

	print "</table>" >> f;
}


