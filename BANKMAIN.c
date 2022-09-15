
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "empDB.h"
#include "cusDB.h"
#include "bankacc.h"


u8 GetuserOptions (void);
u8 Getuser_adminOptions (void);
u8 GetOptions (void);




int main (int argc , char * argv[])
{
	u8 adminflag=0;
	u8 options = 0;
	s8 flag = 0 ;	
	
	
	while (1)
	{
		u8 user_admin = 0 ;
		do{user_admin=Getuser_adminOptions();}while(user_admin==0);
		if(user_admin==1)
		{
			/* if employee is chosen then he need to enter user name and password */
			u8 adminflag 	= ADMINCHECK();
			while(adminflag == 1)
			{
				do{options = GetOptions ();}while(options<1);
				if(options==1)
				{
					CreatAcc();
					options = 0 ;
				}
				else if(options==2)
				{
					openexistingaccount ();
					options = 0 ;
				}
				else if(options==3)
				{
					adminflag=0;
					options = 0 ;
				}
	
				
			}
		}
		else
		{
			cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1} ; 
			char q;
			u8 userflag = 0 ;
			do{
				s_cus=cusCHECK ();
				if(s_cus.state!=0)
				{	printf("again / exit?  1 / 2 \n");
					scanf("\n");
					scanf("%c",&q);
					if(q == '1' )
					{}
					else
					{break;}
				}
				}while(s_cus.state!=0);
			if(checkstatus (&s_cus)==0)
			{printf("accpont not active \n");continue;}
			userflag = 1 ;
			while(userflag ==1 )
			{
					u8 useropflag = 0 ;
					do{useropflag=GetuserOptions ();}while(useropflag==0);
					if(useropflag==3)
					{userflag=0; break;}
					else if (useropflag==1)
					{
						getmony (&s_cus);
					}
					else if (useropflag==2)
					{
						printCusInfo (&s_cus);
					}
					else if (useropflag==4)
					{
						deposit (&s_cus);
					}
					else if (useropflag==5)
					{
						changePass (&s_cus);
					}
					else if (useropflag==6)
					{
						trransop (&s_cus);
					}
			}
			
			
			
		}

	}
	
	
	
}


/*ask for user name and password 
-search if the username and password is correct in the database
 I need to handel the data base*/






//show a list of options return user option 
u8 GetOptions ()
{
		char op [5];
		system("cls");
		printf("pls enter the process \n");
		printf("1 : Creat New Account\n2 : Open Existing Accont\n3 : Exit\n");
		printf("your option is : ");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else if(op[0]=='3')
		{return 3 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}




u8 Getuser_adminOptions ()
{
		char op [5];
		printf("admin 1 : customer 2 \n");
		printf("your option is : \n");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}

u8 GetuserOptions ()
{
		char op [5];
		printf("getcash 1 : getaccount info 2 :quit 3  :deposit 4 : change password 5 :transaction 6\n");
		printf("your option is : \n");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else if(op[0]=='3')
		{return 3 ;}
		else if(op[0]=='4')
		{return 4 ;}
		else if(op[0]=='5')
		{return 5 ;}
		else if(op[0]=='6')
		{return 6 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}

