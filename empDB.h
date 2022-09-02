
#ifndef __EMP_DB_H__

#define	__EMP_DB_H__


#include <string.h>
#include "STD_TYPES.h"


typedef struct{
	char ** _n;
	char ** _p;
	u32 rowsize ;
	u32 strsize ;
}emp_DB_t;
emp_DB_t DB_INIT (void);
int empsearch (emp_DB_t * db , char * name , char * password);


#endif