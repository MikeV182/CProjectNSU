gcc -c account.c
gcc -c btree.c
gcc -c utilities.c
ar rcs libbank.a account.o btree.o utilities.o
gcc main.c -o main -L. -lbank
