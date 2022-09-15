

all: Bank
#	@ dsa_test.exe


# make rule to generate the final binary
Bank:  BANKMAIN.o empDB.o customerDB.o bankacc.o
	@ gcc BANKMAIN.o empDB.o customerDB.o bankacc.o -o APP.exe
	

BANKMAIN.o: empDB.c customerDB.c BANKMAIN.c bankacc.c
	@ gcc -c BANKMAIN.c


empDB.o:empDB.c bankacc.c customerDB.c
	@ gcc -c empDB.c
	
	
customerDB.o:customerDB.c bankacc.c
	@ gcc -c customerDB.c
	
bankacc.o:bankacc.c customerDB.c
	@ gcc -c bankacc.c