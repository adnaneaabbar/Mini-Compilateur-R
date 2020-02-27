all: compilateur

compilateur: compilateur.o analyseur_lexical.o global.o analyseur_syntaxique.o analyseur_semantique.o pseudo_code.o
	gcc -o compilateur compilateur.o analyseur_lexical.o analyseur_syntaxique.o analyseur_semantique.o pseudo_code.o errors.o -g

compilateur.o: compilateur.c analyseur_syntaxique.h global.h analyseur_lexical.h
	gcc -o compilateur.o -c compilateur.c -g

analyseur_syntaxique.o: analyseur_syntaxique.c analyseur_syntaxique.h analyseur_lexical.h global.h errors.h
	gcc -std=gnu99 -o analyseur_syntaxique.o -c analyseur_syntaxique.c -g

analyseur_lexical.o: analyseur_lexical.c global.h errors.h
	gcc -o analyseur_lexical.o -c analyseur_lexical.c -g

analyseur_semantique.o: analyseur_semantique.c analyseur_semantique.h
	gcc -o analyseur_semantique.o -c analyseur_semantique.c -g

pseudo_code.o: pseudo_code.c pseudo_code.h
	gcc -o pseudo_code.o -c pseudo_code.c -g

global.o: errors.c errors.h
	gcc -o errors.o -c errors.c -g

clean:
	rm -rf *.o *.c~ *.h~ *.r~
	rm compilateur



