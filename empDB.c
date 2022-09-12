
#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "empDB.h"
#define DBFILENAME "./employeeDB.txt"
/*
static void parsfilefornamesandpassword (FILE * file ,emp_DB_t * db,u32 size,u32 start);
static void reserve_heap_memory(emp_DB_t * db,u32 size) ;
static u32 DBROWSSIZE (FILE * file);
static void free_heap_memory(emp_DB_t * db , u32 size);
*/

static void rhm(emp_t * s_emp);
static void fhm(emp_t * s_emp);



/*

emp_DB_t DB_INIT (void)
{
	//data base setup
	FILE * empsize =fopen("./embdbsize.txt","rw");
	emp_DB_t DB_ ;

	if(empsize==NULL)
	{printf("file didn't open \n");}
	else
	{
		DB_._MAX=DBROWSSIZE(empsize);
		DB_.strsize=30;
		DB_.rowsize = 30 ;
		//reserve_heap_memory(&DB_);
		//parsfilefornamesandpassword(emp,DB_._n,DB_._p,DB_.rowsize);

	}
	
	fclose(empsize);

	return DB_ ;

}




static u32 DBROWSSIZE (FILE * file)
{
	int j = 1  ;
	u32 size= 0;
	char ch[20] ;
	fgets(ch,20,file);
	for(int i = strlen(ch)-1 ; i >=0 ;i-- )
	{
		size += ((int)(ch[i]-'0'))*j;
		j*=10;
	}
	return size ;
}




static void reserve_heap_memory(emp_DB_t * db , u32 size)
{
		db->_n = (char ** )malloc(size*sizeof(char*));
		db->_p = (char ** )malloc(size*sizeof(char*));

		for(u32 i = 0 ; i < size ; i ++)
		{
			db->_n[i]=(char*)malloc(db->strsize*sizeof(char));
			db->_p[i]=(char*)malloc(db->strsize*sizeof(char));

		}
		
}


static void free_heap_memory (emp_DB_t * db , u32 size)
{
		for(u32 i = 0 ; i < size ; i ++)
		{
			free(db->_n[i]);
			free(db->_p[i]);

		}
		free(db->_p);
		free(db->_n);
		db->_p=NULL;
		db->_n=NULL;
}

static void parsfilefornamesandpassword (FILE*file ,emp_DB_t * db ,u32 size,u32 start)
{
	u32 i= 0 ;	
	reserve_heap_memory(db ,size);
	while (fscanf(file, "%s ",db->_n[i]) == 1 &&fscanf(file, "%s ", db->_p[i]) == 1 )
    {
		i++;		
		if(i==size)
		{break;}
	}
	#if 0
	u32 j = 0 ;
	j=i;
	for(i = 0 ; i < j ; i++)
	{printf("%s \t\t\t\t %s\n",db->_n[i],db->_p[i]);}

	#endif
}


int empsearch (emp_DB_t * db , char * name , char * password)
{
	FILE * file =fopen(DBFILENAME,"r");
	if(file==NULL)
	{printf("file didn't open \n");return 0;}
	u32 REMAINFILEROWS = db->_MAX ;
	u32 _rs = db->rowsize ;
	u32 rownum = 0 ;
	while(_rs<= REMAINFILEROWS)
	{	
		parsfilefornamesandpassword (file,db,_rs,rownum);
		for(int i = 0 ; i < _rs;i++)
		{
			if(db->_n[i][0]==name[0])
			{
				if(strcmp(db->_n[i],name)==0)
				{
					if(strcmp(db->_p[i],password)==0)
					{
						fclose(file);
						free_heap_memory(db,_rs);
						return 1 ;}
					else
					{
						fclose(file);
						free_heap_memory(db,_rs);
						return -2;}
				}
			}
			
		}
		
		free_heap_memory(db,_rs);
		rownum += _rs;
		REMAINFILEROWS-=_rs;
	}
	if(REMAINFILEROWS>0)
	{
		_rs = REMAINFILEROWS;
		parsfilefornamesandpassword (file,db,_rs,rownum);
		for(int i = 0 ; i < _rs;i++)
		{
			if(db->_n[i][0]==name[0])
			{
				if(strcmp(db->_n[i],name)==0)
				{
					if(strcmp(db->_p[i],password)==0)
					{
						fclose(file);
						free_heap_memory(db,_rs);
						return 1 ;
					}
					else
					{
						fclose(file);
						free_heap_memory(db,_rs);
						return -2;
					}
				}
			}
		}
		free_heap_memory(db,_rs);
		
	}
	
	
	fclose(file);
	
	
	return -1 ;
		
}
*/



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