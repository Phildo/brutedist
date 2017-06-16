make: a.out
	

run: password.txt
	

debug:
	gcc -ggdb3 passgen.cpp && gdb ./a.out

a.out: passgen.cpp
	gcc passgen.cpp

password.txt: a.out
	./a.out
