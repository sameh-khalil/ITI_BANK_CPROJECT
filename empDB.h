
#ifndef __EMP_DB_H__

#define	__EMP_DB_H__


#include <string.h>
#include "STD_TYPES.h"

#define		empMRSIZE	30	
/*
typedef struct{
	char ** _n;
	char ** _p;
	u32 rowsize ;
	u32 _MAX ;
	u32 strsize ;
}emp_DB_t;
*/
typedef struct{
	char * _n;
	char * _p;
	u32 strsize ;
	u32 index ;
}emp_t ;

//emp_DB_t DB_INIT (void);
//int empsearch (emp_DB_t * db , char * name , char * password);
emp_t empsearch ( char * name , char * password);


#endif