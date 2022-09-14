

all: Bank
#	@ dsa_test.exe


# make rule to generate the final binary
Bank:  BANKMAIN.o empDB.o customerDB.o
	@ gcc BANKMAIN.o empDB.o customerDB.o -o APP.exe
	

BANKMAIN.o: empDB.c customerDB.c BANKMAIN.c
	@ gcc -c BANKMAIN.c


empDB.o:empDB.c 
	@ gcc -c empDB.c
	
	
customerDB.o:customerDB.c
	@ gcc -c customerDB.c