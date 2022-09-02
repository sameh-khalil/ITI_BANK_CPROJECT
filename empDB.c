
#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "empDB.h"

void parsfilefornamesandpassword (FILE * file, char ** names,char ** password,u32 size);
void reserve_heap_memory(emp_DB_t * db) ;
u32 DBROWSSIZE (FILE * file);

emp_DB_t DB_INIT (void)
{
	//data base setup
	FILE * emp =fopen("./employeeDB.txt","rw");
	FILE * empsize =fopen("./embdbsize.txt","rw");
	emp_DB_t DB_ ;

	if(emp==NULL||empsize==NULL)
	{printf("file didn't open \n");}
	else
	{
		DB_.rowsize=DBROWSSIZE(empsize);
		DB_.strsize=30;
		reserve_heap_memory(&DB_);
		parsfilefornamesandpassword(emp,DB_._n,DB_._p,DB_.rowsize);

	}
	
	fclose(emp);
	fclose(empsize);

	return DB_ ;

}




u32 DBROWSSIZE (FILE * file)
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




void reserve_heap_memory(emp_DB_t * db )
{
		db->_n = (char ** )malloc(db->rowsize*sizeof(char*));
		db->_p = (char ** )malloc(db->rowsize*sizeof(char*));

		for(u32 i = 0 ; i < db->rowsize ; i ++)
		{
			db->_n[i]=(char*)malloc(db->strsize*sizeof(char));
			db->_p[i]=(char*)malloc(db->strsize*sizeof(char));

		}
		
}

void parsfilefornamesandpassword (FILE * file, char ** names,char ** password,u32 size)
{
	u32 i= 0 , j = 0 ;
	while (fscanf(file, "%s ", names[i]) == 1 &&fscanf(file, "%s ", password[i]) == 1 )
    {
		i++;		
		if(i==size)
		{break;}
	}
	#if 0
	j=i;
	for(i = 0 ; i < j ; i++)
	{printf("%s\n",names[i]);}
	printf("--------------\n");
	for(i = 0 ; i < j ; i++)
	{printf("%s\n",password[i]);}
	#endif
}


int empsearch (emp_DB_t * db , char * name , char * password)
{
	for(int i = 0 ; i < db->rowsize;i++)
	{
		if(db->_n[i][0]==name[0])
		{
			if(strcmp(db->_n[i],name)==0)
			{
				if(strcmp(db->_p[i],password)==0)
				{return 1 ;}
				else
				{return -2;}
			}
		}
	}
	return -1 ;
		
}


