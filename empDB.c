
#include <stdio.h>
#include <stdlib.h>
#include "empDB.h"
#define DBFILENAME "./employeeDB.txt"
#include "cusDB.h"
#include "bankacc.h"


static void rhm(emp_t * s_emp);
static void efhm(emp_t * s_emp);






static void rhm(emp_t * s_emp)
{
			s_emp->_n=(char*)malloc(s_emp->strsize*sizeof(char));
			s_emp->_p=(char*)malloc(s_emp->strsize*sizeof(char));
}

static void efhm(emp_t * s_emp)
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
					efhm(&s_emp);
					s_emp._n =NULL;
					s_emp._p =NULL;
					return s_emp;
				}
			}
		}
		i++;
	}
	fclose(file);
	efhm(&s_emp);
	s_emp._n =NULL;
	s_emp._p =NULL;
	return s_emp;

}



int ADMINCHECK ()
{

		char name [30];
		char password [30];
		printf("pls enter username \n");
		scanf("%s",name);
		printf("pls enter password \n");
		scanf("%s",password);
		emp_t s_emp =empsearch(name,password);
		if(s_emp._n==NULL)
		{printf("error\n");return -1;}
		else
		{printf("welc %s\n",s_emp._n);return 1;}
		
}





void CreatAcc ()
{
	cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1};s8 flag = 0 ;
	do{flag=SetAccUserName(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetAccBalance(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetNationalID(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetUserAddress(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetUserAge(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetAccState(&s_cus,1);}while(flag<1);	
	flag = 0 ;
	do{flag=SetGARDIANNationalID(&s_cus);}while(flag<1);
	s_cus._P = (char*)malloc(10 * sizeof(char)) ;
	RandomPass(&s_cus);
	GETBID(&s_cus);
	printCusInfo(&s_cus);
	char ans ;
	do{printf("creat the new acc?  y / n \n");scanf("\n");scanf("%c",&ans);}while(ans!='y'&&ans!='n');
	if(ans=='y')
	{insertcusAtend(&s_cus);fhm(&s_cus);}
	else if(ans=='n')
	{fhm(&s_cus);}
		
}




void openexistingaccount ()
{
	
	u8 flag = 0 ;
	
	char ans = '1' ;
	cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1};
	do
	{
		s_cus = cusCHECK ();
		if(s_cus.state!=0)
		{
			flag = 0;
			printf("again / exit?  1 / 2 \n");
			scanf("\n");
			scanf("%c",&ans);
			if(ans == '1' )
			{flag = 0 ;}
			else
			{return;}
		
		
		}
		else
		{flag = 1 ;}
	}while(flag==0);
	
	
	printCusInfo(&s_cus);
	
	flag=0;
	do
	{
		flag=GetexistingaccOptions();
		if(flag==7)
		{
			fhm(&s_cus);
			printf("quit \n");
			return;
		}
	}while(flag==0);
	
	if(flag==1)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{	trransop (&s_cus);
			fhm(&s_cus);
			return;
		}
	}
	
	
	else if (flag==2)
	{SetAccState(&s_cus,0); return;}


	else if (flag==3)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{deposit(&s_cus);return;}
	}
	else if (flag==5)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{getmony (&s_cus);return;}
	}


	
}





u8 GetexistingaccOptions ()
{
	char ans = '0';
	printf("choose the operation 1: transaction 	2: change account status	3:deposit 	4: return   5: get cash \n");
	scanf("\n");
	scanf("%c",&ans);
	if(ans=='1')
	{return 1 ;}
	else if(ans=='2')
	{return 2 ;}
	else if(ans=='3')
	{return 3 ;}
	else if(ans=='4')
	{return 4 ;}
	else if(ans=='5')
	{return 5 ;}
	
	else if (ans == 'q')
	{return 7 ;}
	else{printf("\nwrong op\n");return 0;}

		

	
}
