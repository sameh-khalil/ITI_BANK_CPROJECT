
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"


typedef struct{
	char ** _n;
	char ** _p;
	u32 rowsize ;
	u32 strsize ;
}emp_DB_t;



void parsfilefornamesandpassword (FILE * file, char ** names,char ** password,u32 size);

void reserve_heap_memory(emp_DB_t * db) ;

u32 DBROWSSIZE (FILE * file);

int main (int argc , char * argv[])
{
	//data base setup
	FILE * emp =fopen("./employeeDB.txt","rw");
	FILE * empsize =fopen("./embdbsize.txt","rw");

	if(emp==NULL||empsize==NULL)
	{printf("file didn't open \n");}
	else
	{
		emp_DB_t DB_ ;
		DB_.rowsize=DBROWSSIZE(empsize);
		DB_.strsize=30;
		
		printf("%d\n",DB_.rowsize);
		reserve_heap_memory(&DB_);
		parsfilefornamesandpassword(emp,DB_._n,DB_._p,DB_.rowsize);
	}
	
	fclose(emp);
	fclose(empsize);
	//system in super loop 

#if 0
	else	
	{
		int i = 0 ;
		int j = 0 ;
		char pars[100][100]  ;
		while(fscanf(emp,"%c",pars[i])==1)
		{
			while()
		}
	}
#endif
	#if 0
	while (1)
	{
			/* if employee is chosen then he need to enter user name and password */
			/*search if the username and password is correct in the database we need to handel the data base*/
			//show a list of options 
				//option 1 creat new account 
					//-ask for full name --check its at least first 4 names (else ask him again )
					//-ask 4 full address 
					//-ask 4 age 
					//ask 4 national id check for 14 digit(else ask him again)
					//-if age < 21 -ask 4 gaurdian national id check for 14 digit(else ask him again)
					//-ask for balance
					//send the new account information and default password 
					//name address nID age bankid accountstatus balance (if age <21)gaurdian nationalid
				
				//option 2 open existing account 
					//showlist of options 
						//1- transaction --bankid
						//2-change account status --bankid
						//3-deposit
						//return to employee options
				
				//option 3 exit
		
		
		
	}
	
	#endif
	
	
	
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
	j=i;
	for(i = 0 ; i < j ; i++)
	{printf("%s\n",names[i]);}
	printf("--------------\n");
	for(i = 0 ; i < j ; i++)
	{printf("%s\n",password[i]);}
}

