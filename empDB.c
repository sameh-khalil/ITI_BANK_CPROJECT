
#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "empDB.h"
#define DBFILENAME "./employeeDB.txt"

static void rhm(emp_t * s_emp);
static void fhm(emp_t * s_emp);






static void rhm(emp_t * s_emp)
{
			s_emp->_n=(char*)malloc(s_emp->strsize*sizeof(char));
			s_emp->_p=(char*)malloc(s_emp->strsize*sizeof(char));
}

static void fhm(emp_t * s_emp)
{
	free(s_emp->_n) ;
	free(s_emp->_p) ;
}

emp_t empsearch ( char * name , char * password)
{

	emp_t s_emp ={NULL,NULL,100};
	FILE * file =fopen(DBFILENAME,"r");
	if(file==NULL)
	{printf("file didn't open \n");return s_emp;}
	rhm(&s_emp);
	
	u32 i = 0 ;
	while (fscanf(file, "%s ",s_emp._n) == 1 &&fscanf(file, "%s ", s_emp._p) == 1 )
    {
		if(s_emp._n[0]==name[0])
		{
			if(strcmp(s_emp._n,name)==0)
			{
				if(strcmp(s_emp._p,password)==0)
				{
					fclose(file);
					s_emp.index = i ;
					return s_emp ;
				}
				else
				{
					fclose(file);
					fhm(&s_emp);
					s_emp._n =NULL;
					s_emp._p =NULL;
					return s_emp;
				}
			}
		}
		i++;
	}
	fclose(file);
	fhm(&s_emp);
	s_emp._n =NULL;
	s_emp._p =NULL;
	return s_emp;

}