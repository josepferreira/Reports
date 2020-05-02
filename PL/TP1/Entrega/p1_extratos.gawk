BEGIN{RS="\n\n"; FS="\n";}

ENDFILE{
	a[FILENAME] = FNR	
}

END{
	for(x in a){
		print "No texto " x " foram encontrados " a[x] " extratos!"
		total += a[x]
	}
	print "No total existem " total " extratos!"
}