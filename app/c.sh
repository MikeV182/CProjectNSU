gcc -c *.c
ar rcs libname.a *.o
gcc main.c -L. -lname -o main