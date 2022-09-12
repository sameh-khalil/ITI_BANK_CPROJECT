
#ifndef __CUS_DB_H__

#define	__CUS_DB_H__


#include <string.h>
#include "STD_TYPES.h"
/*
#define	cusMRSIZE	10	

typedef struct{
	char ** _BID;
	char ** _N;
	char ** _P;
	char ** _S;
	char ** _BAL;
	char ** _nID;
	char ** _ADDR;
	char ** _AGE;	
	char ** _GnID;
	u32 rowsize ;
	u32 _MAX ;
	u32 strsize ;
}cus_DB_t;


cus_DB_t cusDB_INIT (void);
int cussearch (cus_DB_t * db , char * name , char * password);

*/

typedef struct{
	char * _BID;
	char ** _N;
	char * _P;
	char * _S;
	char * _BAL;
	char * _nID;
	char * _ADDR;
	char * _AGE;	
	char * _GnID;
	u32 strsize ;
	u8 state ;
}cus_t;
cus_t cussearch ( char ** name , char * password);


void fhm(cus_t * s_cus);
void insertEditedcus (cus_t * s_new_cus);



#endif