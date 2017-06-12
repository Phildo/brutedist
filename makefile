make: a.out
	

run: password.txt
	

a.out: passgen.c
	gcc passgen.c

password.txt: a.out
	./a.out
