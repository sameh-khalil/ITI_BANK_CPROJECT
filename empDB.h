
#ifndef __EMP_DB_H__

#define	__EMP_DB_H__


#include <string.h>
#include "STD_TYPES.h"

#define		empMRSIZE	30	


typedef struct{
	char * _n;
	char * _p;
	u32 strsize ;
	u32 index ;
}emp_t ;


emp_t empsearch ( char * name , char * password);
int ADMINCHECK(void);
void openexistingaccount (void);
void CreatAcc (void);
u8 GetexistingaccOptions (void);

#endif