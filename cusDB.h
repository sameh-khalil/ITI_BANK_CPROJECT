
#ifndef __CUS_DB_H__

#define	__CUS_DB_H__


#include <string.h>
#include "STD_TYPES.h"


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