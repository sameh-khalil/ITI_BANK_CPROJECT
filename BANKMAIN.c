
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "empDB.h"
#include "cusDB.h"
int ADMINCHECK(void);
u8 GetOptions (void);
cus_t cusCHECK (void);
void printCusInfo (cus_t * s_cus);
int SetAccUserName (cus_t * s_cus);


int main (int argc , char * argv[])
{
	u8 adminflag=0;
	u8 options = 0;
	s8 flag = 0 ;	
	while (1)
	{
		
			/* if employee is chosen then he need to enter user name and password */
			//u8 adminflag 	= ADMINCHECK();
			//cus_DB_t DB_ = cusDB_INIT ();
			cus_t check = cusCHECK(); 
			if(check._N!=NULL){printCusInfo(&check);
			do
			{flag=SetAccUserName(&check);}
			while(flag!=1);
			printCusInfo(&check);
			
			}
//			insertEditedcus (&check);}
			
/*			
			
			int check = cusCHECK(&DB_); 
			if(check >= 0)
			{
				printf("____");
				printf("id %s name %s pass %s",DB_._BID[check],DB_._N[check],DB_._P[check]);
			}
			#if 0
			while(adminflag==1)
			{

				
				options=GetOptions();
				if(options==0)
				{continue ;}
				else if (options==1)
				{}
				else if (options == 2)
				{}
				else if (options == 3)
				{
					adminflag=0;options=0;break;
				}
				//option 1 creat new account 
					//-ask for full name --check its at least first 4 names (else ask him again )%s
					//-ask 4 full address %s 
					//-ask 4 age %s
					//ask 4 national id check for 14 digit(else ask him again)%s
					//-if age < 21 -ask 4 gaurdian national id check for 14 digit(else ask him again)%s
					//-ask for balance %s
					//send the new account information and default password %s
					//account status %s
					//name address nID age bankid accountstatus balance (if age <21)gaurdian nationalid	Password
					//BID	NAME	PASS	STATUS		BALANCE		nID		ADDRESS		AGE		GnID				
				//option 2 open existing account 
					//showlist of options 
						//1- transaction --bankid
						//2-change account status --bankid
						//3-deposit
						//return to employee options
				
				//option 3 exit
			}
			#endif

		
	*/
	}
	
	
	
}


/*ask for user name and password 
-search if the username and password is correct in the database
 I need to handel the data base*/

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
		{printf("error\n");return-1;}
		else
		{printf("welc %s",s_emp._n);return 1;}
		
}


cus_t cusCHECK ()
{
	/*
		char name [30];
		char password [30];
		printf("pls enter username \n");
		scanf("%s",name);
		printf("pls enter password \n");
		scanf("%s",password);
		u8 thereis = cussearch(DB_,name,password);
		if(thereis>=0)
		{printf("cus %s \n",name);return thereis;}
		else if (thereis==-1)
		{printf("wrong username \n");return -1;}
		else if (thereis==-2)
		{printf("wrong password \n");return -1;}
	*/
	char ** name = (char **)malloc(4*sizeof(char*));
	name[0] = (char *)malloc(15*sizeof(char));
	name[1] = (char *)malloc(15*sizeof(char));
	name[2] = (char *)malloc(15*sizeof(char));
	name[3] = (char *)malloc(15*sizeof(char));
	char password [30];
	printf("pls enter username \n");
	scanf("%s",name[0]);
	scanf("%s",name[1]);
	scanf("%s",name[2]);
	scanf("%s",name[3]);
	printf("pls enter password \n");
	scanf("%s",password);
	cus_t s_cus =cussearch(name,password);

	if(s_cus.state==2)
	{

		fhm(&s_cus);
		printf("no such name\n");
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;}
		
	else if(s_cus.state==1)
	{
		fhm(&s_cus);
		printf("wrong Password\n");
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;
	}
	else
	{
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;
	}
}

/*
int ctry ()
{
	
		char name [30];
		char password [30];
		printf("pls enter username \n");
		scanf("%s",name);
		printf("pls enter password \n");
		scanf("%s",password);
		u8 thereis = cussearch(DB_,name,password);
		if(thereis>=0)
		{printf("cus %s \n",name);return thereis;}
		else if (thereis==-1)
		{printf("wrong username \n");return -1;}
		else if (thereis==-2)
		{printf("wrong password \n");return -1;}
	

	try();

}
*/




void printCusInfo (cus_t * s_cus)
{
	printf("Bank ID\t: %s\n",s_cus->_BID	);
	printf("NAME\t: %s %s %s %s \n",s_cus->_N[0],s_cus->_N[1],s_cus->_N[2],s_cus->_N[3]		);
	//printf(": %s\n",s_cus->_P		);
	printf("STATUS\t: %s\n",s_cus->_S		);
	printf("BALANCE\t: %s\n",s_cus->_BAL	);
	printf("national id: %s\n",s_cus->_nID	);
	printf("address: %s\n",s_cus->_ADDR	);
	printf("Age\t: %s\n",s_cus->_AGE	);
	printf("gid\t: %s\n",s_cus->_GnID	);
}













//show a list of options return user option 
u8 GetOptions ()
{
		char op ;
		printf("pls enter the process \n");
		printf("1 : Creat New Account\n2 : Open Existing Accont\n3 : Exit\n");
		printf("your option is : ");
		scanf("%c",&op);
		if(op=='1')
		{return 1 ;}
		else if(op=='2')
		{return 2 ;}
		else if(op=='3')
		{return 3 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}



int SetAccUserName (cus_t * s_cus)
{
	char ** fullname = (char**)malloc(4*sizeof(char*));
	fullname[0] = (char*)malloc(15*sizeof(char));
	fullname[1] = (char*)malloc(15*sizeof(char));
	fullname[2] = (char*)malloc(15*sizeof(char));
	fullname[3] = (char*)malloc(15*sizeof(char));
	printf("enter the username in the following format \"1st 2nd 3d 4th\" :\n");
	scanf("%s",fullname[0]);
	scanf("%s",fullname[1]);
	scanf("%s",fullname[2]);
	scanf("%s",fullname[3]);
	for(int i = 0 ; i < 4 ; i++)
	{
		if(strlen(fullname[i])<=1)
		{
			printf("too short\n");
			return -1;
		}
		if (strlen(fullname[i])>=15)
		{
			printf("too long\n");
			return -1 ;
		}
		u8 j = 0 ;
		while(fullname[i][j]!='\0')
		{
			if(!((fullname[i][j]>='a'&&fullname[i][j]<='z')||(fullname[i][j]>='A'&&fullname[i][j]<='Z')))
			{
				printf("cant accept any nums or sympols \n");
				return-1;
			}
			j++;
		}
	}

	s_cus->_N=fullname;
	
	return 1 ;
}